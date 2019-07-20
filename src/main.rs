use ggez::{Context, ContextBuilder, GameResult};
use ggez::event::{self, EventHandler};
use ggez::graphics::{self, Rect, Mesh, DrawMode, FillOptions};

mod grid;

use grid::{GoLGrid, NeighbourIter};

fn conways_rules(_: usize, _: usize, c: bool, neighs: NeighbourIter) -> bool {
    let alive_count = neighs.filter(|ic| *ic).count();

    if alive_count < 2 || alive_count > 3 {
        false
    } else if alive_count == 3 {
        true
    } else {
        c
    }
}

struct Lyfe {
    grid: GoLGrid,
    grid_cells: Vec<bool>,
}

impl Lyfe {
    pub fn new(_ctx: &mut Context, size: usize) -> Self {
        let grid = GoLGrid::from_luck(size, 0.3);
        let grid_cells = grid.iter().copied().collect();

        Self {
            grid,
            grid_cells, 
        }
    }
}

impl EventHandler for Lyfe {
    fn update(&mut self, _ctx: &mut Context) -> GameResult<()> {
        self.grid.apply_rules(conways_rules);

        Ok(())
    }

    fn draw(&mut self, ctx: &mut Context) -> GameResult<()> {
        const CELL_SIZE: f32 = 10.;
        
        graphics::clear(ctx, graphics::BLACK);

        let mut cell_rect = Rect::zero();
        cell_rect.w = CELL_SIZE - 2.;
        cell_rect.h = CELL_SIZE - 2.;

        for (i, c) in self.grid.iter().enumerate() {
            let x = (i % self.grid.size()) as f32;
            let y = (i / self.grid.size()) as f32;
            
            let rect_mesh = Mesh::new_rectangle(
                ctx,
                DrawMode::Fill(FillOptions::DEFAULT),
                cell_rect,
                if *c { graphics::WHITE } else { graphics::BLACK }
            )?;
            
            graphics::draw(ctx, &rect_mesh, ([x*CELL_SIZE+1., y*CELL_SIZE+1.],))?;
        }

        graphics::present(ctx)
    }
}

fn main() -> GameResult {
    let (mut ctx, mut event_loop) = ContextBuilder::new("lyfe", "strexicious").build()?;
    let mut my_game = Lyfe::new(&mut ctx, 75);

    match event::run(&mut ctx, &mut event_loop, &mut my_game) {
        Ok(_) => println!("Exited cleanly."),
        Err(e) => println!("Error occured: {}", e)
    }

    Ok(())
}

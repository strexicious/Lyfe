use ggez::{Context, ContextBuilder, GameResult};
use ggez::event::{self, EventHandler, KeyCode};
use ggez::input::keyboard::{KeyMods};
use ggez::input::mouse::{MouseButton};
use ggez::graphics::{self, Rect, MeshBuilder, DrawMode, FillOptions};

mod grid;

use grid::{GoLGrid, NeighbourIter};

const CELL_SIZE: f32 = 10.;

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
    grid_pattern: Vec<bool>,
    simulating: bool,
    changed: bool,
}

impl Lyfe {
    pub fn new(_ctx: &mut Context, size: usize) -> Self {
        let grid = GoLGrid::from_luck(size, 0.3);
        let grid_pattern = grid.iter().copied().collect();

        Self {
            grid,
            grid_pattern, 
            simulating: false,
            changed: false,
        }
    }

    fn toggle_simulation(&mut self) {
        if self.changed {
            self.changed = false;
            self.grid = GoLGrid::from_pattern(self.grid_pattern.clone(), self.grid.size());
        }
        
        self.simulating = !self.simulating;
        
        if !self.simulating {
            self.grid_pattern = self.grid.iter().copied().collect();
        }
    }

    fn clear_grid(&mut self) {
        self.grid_pattern = vec![false; self.grid.size().pow(2)];
        self.grid = GoLGrid::from_pattern(self.grid_pattern.clone(), self.grid.size());
    }

    fn regen_random_grid(&mut self) {
        self.grid = GoLGrid::from_luck(self.grid.size(), 0.3);
        self.grid_pattern = self.grid.iter().copied().collect();
    }
}

impl EventHandler for Lyfe {
    fn update(&mut self, _ctx: &mut Context) -> GameResult<()> {
        if self.simulating {
            self.grid.apply_rules(conways_rules);
        }

        Ok(())
    }

    fn draw(&mut self, ctx: &mut Context) -> GameResult<()> {
        graphics::clear(ctx, graphics::BLACK);

        let mut cell_rect = Rect::zero();
        cell_rect.w = CELL_SIZE - 2.;
        cell_rect.h = CELL_SIZE - 2.;
        let mut rect_mb = MeshBuilder::new();

        let cell_iter = if self.simulating {
            self.grid.iter()
        } else {
            self.grid_pattern.iter()
        };

        for (i, c) in cell_iter.enumerate() {
            let x = (i % self.grid.size()) as f32;
            let y = (i / self.grid.size()) as f32;
            
            cell_rect.move_to([x*CELL_SIZE+1., y*CELL_SIZE+1.]);
            
            rect_mb.rectangle(
                DrawMode::Fill(FillOptions::DEFAULT),
                cell_rect,
                if *c { graphics::WHITE } else { graphics::BLACK }
            );
            
        }

        let rect_mesh = rect_mb.build(ctx)?;
        graphics::draw(ctx, &rect_mesh, ([0.,0.],))?;
        graphics::present(ctx)
    }

    fn key_down_event(
        &mut self,
        ctx: &mut Context,
        keycode: KeyCode,
        _keymods: KeyMods,
        _repeat: bool
    ) {
        match keycode {
            KeyCode::S => self.toggle_simulation(),
            KeyCode::R => self.regen_random_grid(),
            KeyCode::C => self.clear_grid(),
            KeyCode::Escape => event::quit(ctx),
            _ => ()
        }
    }

    fn mouse_button_down_event(
        &mut self,
        _ctx: &mut Context,
        button: MouseButton,
        x: f32,
        y: f32
    ) {
        if button == MouseButton::Left && !self.simulating {
            let col = (x / CELL_SIZE) as usize;
            let row = (y / CELL_SIZE) as usize;
            let cell_idx = row * self.grid.size() + col;

            self.grid_pattern[cell_idx] = !self.grid_pattern[cell_idx];
            self.changed = true;
        }
    }
}

fn main() -> GameResult {
    let (mut ctx, mut event_loop) = ContextBuilder::new("lyfe", "strexicious").build()?;
    let mut my_game = Lyfe::new(&mut ctx, 60);

    match event::run(&mut ctx, &mut event_loop, &mut my_game) {
        Ok(_) => println!("Exited cleanly."),
        Err(e) => println!("Error occured: {}", e)
    }

    Ok(())
}

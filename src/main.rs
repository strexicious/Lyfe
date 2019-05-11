mod grid;

use grid::{GoLGrid};

fn print_grid(g: &GoLGrid, size: usize) {
    for (i, c) in g.iter().enumerate() {
        if i % size == 0 {
            print!("[");
        }

        print!(" {}", if *c { "■" } else { " " });
        
        if i % size == size - 1 {
            println!(" ]");
        }
    }
}

const SIZE: usize = 10;
const PATTERN: &str = "
-X--------
--X-------
XXX-------
----------
----------
----------
----------
----------
----------
----------
";

fn main() {    
    let mut gol = GoLGrid::from_pattern(
    PATTERN.chars()
        .filter(|c| *c != '\n')
        .map(|c| c == 'X')
        .collect()
    , SIZE);

    print_grid(&gol, SIZE);

    for _ in 0..10 {
        gol.apply_rules(|_, _, c, neighs| -> bool {
            let alive_count = neighs.filter(|ic| *ic).count();
            if alive_count < 2 || alive_count > 3 {
                false
            } else if alive_count == 3 {
                true
            } else {
                c
            }
        });

        println!();
        print_grid(&gol, SIZE);
    }
}

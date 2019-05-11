use std::slice::Iter;
use rand::distributions::{Bernoulli, Distribution};

pub struct NeighbourIter {
    neighs: [bool; 8],
    current: usize,
}

impl Iterator for NeighbourIter {
    type Item = bool;

    fn next(&mut self) -> Option<Self::Item> {
        if self.current < self.neighs.len() {
            self.current += 1;
            Some(self.neighs[self.current - 1])
        } else {
            None
        }
    }
}

pub struct GoLGrid {
    new_buf: Box<[bool]>,
    cur_buf: Box<[bool]>,
    size: usize,
}

impl GoLGrid {
    pub fn new(size: usize, alive_chance: f64) -> Self {
        let rng = &mut rand::thread_rng();
        let dist = Bernoulli::new(alive_chance);
        let dist_iter = dist.sample_iter(rng);

        if size == 0 {
            panic!("Size must be at least 1");
        }

        Self {
            new_buf: vec![false; size * size].into_boxed_slice(),
            cur_buf: dist_iter.take(size * size).collect(),
            size
        }
    }

    pub fn from_pattern(pat: Vec<bool>, size: usize) -> Self {
        if pat.len() < size * size {
            panic!("Pattern is smaller than the number of cells: {}", size * size);
        }

        Self {
            new_buf: vec![false; size * size].into_boxed_slice(),
            cur_buf: pat.into_boxed_slice(),
            size
        }
    }

    pub fn get_neighbours(&self, x: usize, y: usize) -> NeighbourIter {
        let left_col = if x == 0 { self.size - 1} else { x - 1};
        let right_col = if x == self.size - 1 { 0 } else { x + 1 };
        let top_row = if y == 0 { self.size - 1} else { y - 1 };
        let bottom_row = if y == self.size - 1 { 0 } else { y + 1 };

        NeighbourIter {
            neighs: [
                self.cur_buf[left_col  + top_row    * self.size],
                self.cur_buf[x         + top_row    * self.size],
                self.cur_buf[right_col + top_row    * self.size],
                self.cur_buf[left_col  + y          * self.size],
                self.cur_buf[right_col + y          * self.size],
                self.cur_buf[left_col  + bottom_row * self.size],
                self.cur_buf[x         + bottom_row * self.size],
                self.cur_buf[right_col + bottom_row * self.size],
            ],
            current: 0
        }
    }

    pub fn apply_rules<F>(&mut self, mut rules: F)
        where F: FnMut(usize, usize, bool, NeighbourIter) -> bool
    {
        for y in 0..self.size {
            for x in 0..self.size {
                let neighs = self.get_neighbours(x, y);
                let i = x + y * self.size;

                self.new_buf[i] = rules(x, y, self.cur_buf[i], neighs);
            }
        }
        std::mem::swap(&mut self.cur_buf, &mut self.new_buf);
    }

    pub fn iter(&self) -> Iter<bool> {
        self.cur_buf.iter()
    }
}

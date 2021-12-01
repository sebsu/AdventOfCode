use std::io;
use std::io::BufRead;
use std::collections::VecDeque;

fn main() {
    let stdin = io::stdin();
    let mut n_incr: i32 = 0;
    let mut prev_depth = 0;
    let mut depths: VecDeque<i32> = VecDeque::with_capacity(3);
    for line in stdin.lock().lines() {
        let reading: i32 = line.unwrap().parse().unwrap();
        depths.push_front(reading);
        if depths.len() < 3 {
            continue;
        }
        let mut depth = 0;
        for d in depths.iter() {
            depth = depth + d;
        }
        //println!("Depth: {}", depth);
        if prev_depth < depth {
            n_incr += 1;
        }
        prev_depth = depth;
        depths.pop_back();
    }
    println!("Result: {}", n_incr-1);
}
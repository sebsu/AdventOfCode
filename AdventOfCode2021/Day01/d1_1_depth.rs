use std::io;
use std::io::BufRead;

fn main() {
    let stdin = io::stdin();
    let mut prev_depth: i32 = 0;
    let mut n_incr: i32 = 0;
    
    for line in stdin.lock().lines() {
        let depth: i32 = line.unwrap().parse().unwrap();
        if (prev_depth < depth) {
            n_incr += 1;
        }
        prev_depth = depth;
    }
    println!("Result: {}", n_incr-1);
}
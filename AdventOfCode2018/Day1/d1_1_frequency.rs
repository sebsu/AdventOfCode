use std::fs::File;
use std::io::prelude::*;

fn main() {
    let mut input = String::new();
    let mut res = 0;
    let mut file = File::open("input.txt").expect("File not found!");
    file.read_to_string(&mut input)
        .expect("Failed to read file.");
    let freq = input.split_whitespace();
    for f in freq {
        let change: i64 = f.trim().parse().expect("Not a valid number");
        res = res + change;
    }
    println!("Final result is {}", res);
}

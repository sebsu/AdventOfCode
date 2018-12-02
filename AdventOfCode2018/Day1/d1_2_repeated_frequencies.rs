use std::collections::HashMap;
use std::fs::File;
use std::io::prelude::*;

fn main() {
    let mut input = String::new();
    let mut res = 0;
    let mut file = File::open("input.txt").expect("File not found!");
    file.read_to_string(&mut input)
        .expect("Failed to read file.");
    let mut prev: HashMap<i64, i64> = HashMap::new();

    loop {
        let freq = input.split_whitespace(); //Can't use this outside of loop(?)
        for f in freq {
            let change: i64 = f.trim().parse().expect("Not a valid number");
            res = res + change;
            if prev.contains_key(&res) {
                println!("Final freq is {}", res);
                return;
            } else {
                prev.insert(res, 1);
            }
        }
    }
}

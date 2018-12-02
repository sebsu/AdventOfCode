use std::fs::File;
//use std::io;
use std::io::prelude::*;

fn main() {
    let mut input = String::new();
    let mut res = 0;
    let mut file = File::open("input.txt").expect("File not found!");
    file.read_to_string(&mut input)
        .expect("Failed to read file.");
    let freq = input.split_whitespace();
    for f in freq {
        let change: i64 = match f.trim().parse() {
            Ok(num) => num,
            Err(_) => {
                println!("Something broke");
                break;
            }
        };
        res = res + change;
    }
    //println!("Final result is {}", res);
    println!("{}", res);
}

use std::fs::File;
use std::io::prelude::*;

fn main() {
    let mut input = String::new();
    let mut file = File::open("input.txt").expect("File not found!");
    file.read_to_string(&mut input)
        .expect("Failed to read file.");
    let poly_vec: Vec<char> = input.trim().chars().collect();
    let mut res: Vec<char> = Vec::new();
    
    let mut prev = ' ';

    for c in poly_vec {
        if (c.is_lowercase() && c.to_ascii_uppercase() == prev)
            || (c.is_uppercase() && c.to_ascii_lowercase() == prev)
        {
            res.pop();
            prev = match res.pop() {
                Some(val) => val,
                None => ' ',
            };
            if prev != ' ' {
                res.push(prev);
            }
        } else {
            res.push(c);
            prev = c;
        }
    }

    // println!("{:?}, len {}", res, res.len());
    println!("Length: {}", res.len());
}

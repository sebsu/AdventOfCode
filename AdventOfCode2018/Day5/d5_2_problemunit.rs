use std::fs::File;
use std::io::prelude::*;

fn main() {
    let mut input = String::new();
    let mut file = File::open("input.txt").expect("File not found!");
    file.read_to_string(&mut input)
        .expect("Failed to read file.");
    let polymer: Vec<char> = input.trim().chars().collect();

    let mut res: Vec<char> = Vec::new();
    let mut shortest = <usize>::max_value();
    let alpha: Vec<char> = "abcdefghijklmnopqrstuvwxyz".chars().collect();
    for c in alpha {
        let cleaned = clean_polymer(&polymer, c);
        let collapsed = collapse(cleaned);
        if collapsed.len() < shortest {
            res = collapsed;
            shortest = res.len();
        }
    }

    // println!("{:?}, len {}", res, res.len());
    println!("Length: {}", res.len());
}

fn clean_polymer(polymer: &Vec<char>, del: char) -> Vec<char> {
    let mut out: Vec<char> = Vec::new();
    for c in polymer {
        if !c.eq_ignore_ascii_case(&del) {
            out.push(*c);
        }
    }
    out
}

fn collapse(polymer: Vec<char>) -> Vec<char> {
    let mut res: Vec<char> = Vec::new();
    let mut prev = ' ';

    for c in polymer {
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
    res
}

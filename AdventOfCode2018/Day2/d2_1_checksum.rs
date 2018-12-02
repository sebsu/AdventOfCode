use std::collections::HashMap;
use std::fs::File;
use std::io::prelude::*;

fn main() {
    let mut input = String::new();
    let mut file = File::open("input.txt").expect("File not found!");
    file.read_to_string(&mut input)
        .expect("Failed to read file.");
    let ids = input.split_whitespace();
    let mut count_2 = 0;
    let mut count_3 = 0;
    for id in ids {
        let mut occurences: HashMap<char, i64> = HashMap::new();
        for c in id.chars() {
            let count = match occurences.get(&c) {
                Some(val) => *val,
                None => 0,
            };
            occurences.insert(c, count + 1);
        }

        let mut found_2 = false;
        let mut found_3 = false;
        for key in occurences.keys() {
            let count = match occurences.get(key) {
                Some(val) => *val,
                None => continue,
            };
            if count == 2 && !found_2 {
                count_2 = count_2 + 1;
                found_2 = true;
            } else if count == 3 && !found_3 {
                count_3 = count_3 + 1;
                found_3 = true;
            }
        }
    }
    println!("{} * {} = {}", count_2, count_3, count_2 * count_3);
}

use std::collections::HashMap;
use std::fs::File;
use std::io::prelude::*;

fn main() {
    let mut input = String::new();
    let mut file = File::open("input.txt").expect("File not found!");
    file.read_to_string(&mut input)
        .expect("Failed to read file.");
    let ids = input.split_whitespace();

    let mut id_hash: HashMap<usize, String> = HashMap::new();
    let mut size = 0;
    for (i, id) in ids.enumerate() {
        id_hash.insert(i, id.to_string());
        size = i+1;
    }
    
    let mut res = String::new();
    for i in 0..size {
        let id_1 = match id_hash.get(&i) {
            Some(val) => val,
            None => break,
        };
        for j in i..size {
            let id_2 = match id_hash.get(&j) {
                Some(val) => val,
                None => break,
            };
            if id_1 == id_2 || id_1.len() != id_2.len() {
                continue;
            }

            for k in 0..id_1.len() {
                let mut res_1 = String::new();
                let mut res_2 = String::new();
                let (first, _) = id_1.split_at(k);
                let (_, last) = id_1.split_at(k+1);
                res_1.push_str(first);
                res_1.push_str(last);
                let (first, _) = id_2.split_at(k);
                let (_, last) = id_2.split_at(k+1);
                res_2.push_str(first);
                res_2.push_str(last);
                if res_1 == res_2 {
                    res = res_1;
                    break;
                }
            }
            
            if !res.is_empty() {
                break;
            }
        }

        if !res.is_empty() {
            break;
        }
    }
    println!("{}", res);
}

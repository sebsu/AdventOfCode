use std::collections::HashMap;
use std::fs::File;
use std::io::prelude::*;

fn main() {
    let mut input = String::new();
    let mut file = File::open("input.txt").expect("File not found!");
    file.read_to_string(&mut input)
        .expect("Failed to read file.");
    let mut fabric: HashMap<String, u32> = HashMap::new();

    for line in input.lines() {
        let (mut coord, mut size) = line.split_at(line.find(":")
                                                  .expect("Can't find ':'"));
        let (_, coord) = coord.split_at(coord.find("@ ")
                                        .expect("Can't find '@ '") + 2);
        size = size.trim_start_matches(": ");

        let (sx_str, mut sy_str) = coord.split_at(coord.find(",")
                                                  .expect("Can't find '@ '"));
        let mut sx = sx_str.parse::<u32>().unwrap();
        let mut sy = sy_str.trim_start_matches(",").parse::<u32>().unwrap();

        let (nx_str, mut ny_str) = size.split_at(size.find("x")
                                                 .expect("Can't find 'x'"));
        let mut nx = nx_str.parse::<u32>().unwrap();
        let mut ny = ny_str.trim_start_matches("x").parse::<u32>().unwrap();

        for i in 0..nx {
            let x = sx + i;
            let mut x_str = x.to_string();
            x_str.push(',');
            for j in 0..ny {
                let y = sy + j;
                let mut coord_str = x_str.to_owned();
                coord_str.push_str(&y.to_string());
                let mut n = match fabric.get(&coord_str) {
                    Some(val) => *val,
                    None => 0,
                };
                fabric.insert(coord_str, n + 1);
            }
        }
    }

    let mut overlap = 0;
    for key in fabric.keys() {
        let count = fabric.get(key).expect("No such key");
        if *count > 1 {
            overlap = overlap + 1;
        }
    }
    println!("Overlapping {}", overlap);
}

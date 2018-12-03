use std::collections::HashMap;
use std::fs::File;
use std::io::prelude::*;

fn main() {
    let mut input = String::new();
    let mut file = File::open("input.txt").expect("File not found!");
    file.read_to_string(&mut input)
        .expect("Failed to read file.");
    let mut fabric: HashMap<String, Vec<u32>> = HashMap::new();
    let mut unique: HashMap<u32, u32> = HashMap::new();

    for line in input.lines() {
        let (mut coord, mut size) = line.split_at(line.find(":")
                                                  .expect("Can't find ':'"));
        let (mut id_str, coord) = coord.split_at(coord.find("@ ")
                                                 .expect("Can't find '@ '") + 2);
        
        // Getting the claim id and enters it into a hashmap for later
        id_str = id_str.trim().trim_matches('#').trim_matches('@').trim();
        let id = id_str.parse::<u32>().unwrap();
        unique.insert(id, 1);
        
        // Getting the starting coordinates as ints
        let (sx_str, mut sy_str) = coord.split_at(coord.find(",")
                                                  .expect("Can't find ','"));
        let mut sx = sx_str.parse::<u32>().unwrap();
        let mut sy = sy_str.trim_start_matches(",").parse::<u32>().unwrap();
        
        // Getting the patch size as ints
        size = size.trim_start_matches(": ");
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
                // Saving the coord as a string for unique keys in the hashmap
                let mut coord_str = x_str.to_owned();
                coord_str.push_str(&y.to_string());
                // Enter the id into a vec of claims that has claimed that spot
                fabric.entry(coord_str).or_insert_with(Vec::new).push(id);
            }
        }
    }

    for coord in fabric.keys() {
        let visited = fabric.get(coord).expect("No such key");
        if visited.len() > 1 { // If more than one has claimed this spot
            for id in visited { // none of the claims are valid.
                unique.remove(id);
            }
        }
    }

    for id in unique.keys() { // Should be only one, but why not print all
        println!("Claim with no overlap: {}", id);
    }
}

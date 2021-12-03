use std::io;
use std::io::BufRead;
use std::str;

fn main() {
    let stdin = io::stdin();
    let mut depth: i32 = 0;
    let mut horisontal: i32 = 0;
    for line in stdin.lock().lines() {
        let reading = line.unwrap();
        let mut reading = reading.split_whitespace();
        let dir  = reading.next();
        match dir.unwrap() {
            "forward" => horisontal += reading.next().unwrap().parse::<i32>().unwrap(),
            "down" => depth += reading.next().unwrap().parse::<i32>().unwrap(),
            "up" => depth -= reading.next().unwrap().parse::<i32>().unwrap(),
            _ => println!("Ain't special"),
        }
        //println!("dir: {}, d {}, h {}", dir.unwrap(), depth, horisontal);
        
    }
    println!("Result: {}", depth*horisontal);
}
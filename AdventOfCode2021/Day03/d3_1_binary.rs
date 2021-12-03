use std::io;
use std::io::BufRead;
use std::str;

//const N_BITS: usize = 5; // Testing
const N_BITS: usize = 12; // Real shit

fn calc_gamma(arr: &[i32; N_BITS]) -> i32 {
    let mut res: i32 = 0;
    for i in arr {
        res = res<<1;
        if i>&0 {
            res += 1;
        }
    }
    res
}

fn main() {
    let stdin = io::stdin();
    let mut binary: [i32; N_BITS] = [0; N_BITS];
    for line in stdin.lock().lines() {
        let reading = line.unwrap();
        let mut pos: usize = 0;
        for ch in reading.chars() {
            if ch == '0' {
                binary[pos] -= 1;
            } else {
                binary[pos] += 1;
            }
            pos += 1;
        }
        //println!("dir: {}, d {}, h {}", dir.unwrap(), depth, horisontal);
    }
    let mut inv: i32 = 0;
    for _ in 0..N_BITS {
        inv = inv<<1;
        inv += 1;
    }
    let gamma: i32 = calc_gamma(&binary);
    let epsilon: i32 = gamma^inv; //Bit invert the gamma to get epsilon.
    println!("Result: {}", gamma*epsilon);
}
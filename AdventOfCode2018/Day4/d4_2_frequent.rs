use std::collections::HashMap;
use std::fs::File;
use std::io::prelude::*;

fn main() {
    let mut input = String::new();
    let mut file = File::open("input.txt").expect("File not found!");
    file.read_to_string(&mut input)
        .expect("Failed to read file.");
    let mut events: Vec<&str> = input.lines().collect();
    events.sort();
    let mut sleeping_schedule: HashMap<u32, [u32; 60]> = HashMap::new();

    let mut curr_guard = 0;
    let mut fell_asleep_at = 0;
    for event in events {
        if event.contains("Guard") {
            curr_guard = get_guard(event);
        } else if event.contains("falls") {
            fell_asleep_at = get_minute(event);
        } else if event.contains("wakes") {
            let woke_up_at = get_minute(event);

            let mut sleep: [u32; 60] = [0; 60];
            if sleeping_schedule.contains_key(&curr_guard) {
                sleep = match sleeping_schedule.get_mut(&curr_guard) {
                    Some(val) => *val,
                    None => break,
                };
            }
            for i in 0..60 {
                let is_sleeping = (fell_asleep_at <= i && i < woke_up_at) as u32;
                sleep[i as usize] = sleep[i as usize] + is_sleeping;
            }
            sleeping_schedule.insert(curr_guard, sleep);
        }
    }

    let mut sleepiest = 0;
    let mut amount = 0;
    let mut minute = 0;
    for guard in sleeping_schedule.keys() {
        let max = max_array(*sleeping_schedule.get(guard).expect("No guard?"));
        if max > amount {
            sleepiest = *guard;
            amount = max;
            minute = max_array_index(*sleeping_schedule.get(guard).expect("No guard?"));
        }
    }
    println!("Guard: {}. Minute: {}. Amount: {}.Hash: {}", sleepiest, minute, amount, sleepiest*minute);
    for x in 0..60 {
        print!("{} ", sleeping_schedule.get(&sleepiest).expect("No guard?")[x]);
    }
}

// fn sum_array(arr: [u32; 60]) -> u32 {
//     let mut sum = 0;
//     for i in 0..60 {
//         sum = sum + arr[i];
//     }
//     sum
// }

fn max_array(arr: [u32; 60]) -> u32 {
    let mut max = 0;
    for i in 0..60 {
        if max < arr[i] {
            max = arr[i];
        }
    }
    max
}

fn max_array_index(arr: [u32; 60]) -> u32 {
    let mut max = 0;
    let mut index = 0;
    for i in 0..60 {
        if max < arr[i] {
            max = arr[i];
            index = i;
        }
    }
    index as u32
}

fn get_guard(e: &str) -> u32 {
    let (_, num) = e.split_at(e.find("#").expect("Can't find '#'") + 1);
    let (num, _) = num.split_at(num.find(" ").expect("Can't find ' '"));
    num.parse::<u32>().unwrap()
}
fn get_minute(e: &str) -> u32 {
    let (_, num) = e.split_at(e.find(":").expect("Can't find ':'") + 1);
    let (num, _) = num.split_at(num.find("]").expect("Can't find ']'"));
    num.parse::<u32>().unwrap()
}

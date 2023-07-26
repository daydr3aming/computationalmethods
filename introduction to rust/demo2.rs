use rand::prelude::*;

fn main() {
    // Se llama un macro, no una funcion en sí.
    // I32 es integer
    let mut rng = thread_rng();
    let x: i32 = rng.gen_range(0..=1);
    println!("x is = {}", x);

    if x == 1{
        println!("Tails!")
    }else{
        println!("Heads!")
    }
}
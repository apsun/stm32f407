#![no_std]
#![feature(alloc_error_handler)]

#[macro_use]
extern crate alloc;

mod mem;
mod panic;

#[no_mangle]
pub extern "C" fn get_item(index: i32) -> i32 {
    vec![4, 42, 69, 420, 1337][index as usize]
}

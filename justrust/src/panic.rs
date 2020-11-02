use core::cmp::min;
use core::fmt::Result;
use core::fmt::Write;
use core::panic::PanicInfo;

extern "C" {
    fn abort(c_str: *const u8) -> !;
}

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    let mut buf = [0u8; 4096];
    let mut writer = ArrayWriter::new(&mut buf);
    write!(&mut writer, "{}", info).unwrap();
    unsafe {
        abort(writer.c_str());
    }
}

// TODO: No idea what this is
#[no_mangle]
fn __aeabi_unwind_cpp_pr0() -> ! {
    loop {}
}

// TODO: No idea what this is either
#[no_mangle]
fn __aeabi_unwind_cpp_pr1() -> ! {
    loop {}
}

struct ArrayWriter<'a> {
    data: &'a mut [u8],
    offset: usize,
}

impl<'a> Write for ArrayWriter<'a> {
    fn write_str(&mut self, s: &str) -> Result {
        let n = min(s.len(), self.data.len() - self.offset - 1);
        self.data[self.offset..self.offset + n].copy_from_slice(&s.as_bytes()[..n]);
        self.offset += n;
        Ok(())
    }
}

impl<'a> ArrayWriter<'a> {
    fn new(data: &'a mut [u8]) -> ArrayWriter<'a> {
        assert!(data.len() >= 1);
        ArrayWriter {
            data: data,
            offset: 0,
        }
    }

    fn c_str(&mut self) -> *const u8 {
        self.data[self.offset] = 0u8;
        return self.data.as_ptr();
    }
}

use core::alloc::GlobalAlloc;
use core::alloc::Layout;
use core::cell::RefCell;
use core::ptr::null_mut;

struct BumpAllocatorImpl {
    mem: [u8; 4096],
    offset: usize,
}

impl BumpAllocatorImpl {
    fn alloc(&mut self, layout: Layout) -> *mut u8 {
        let start = (self.offset + layout.align() - 1) & !(layout.align() - 1);
        let end = start.wrapping_add(layout.size());
        if end < start || end >= self.mem.len() {
            return null_mut();
        }
        self.offset = end;
        return &mut self.mem[start];
    }

    fn dealloc(&mut self, _ptr: *mut u8, _layout: Layout) {
        // No-op
    }
}

// Needed because GlobalAlloc takes &self and not &mut self.
// This should be okay for now since we're single threaded for the
// foreseeable future.
struct BumpAllocator {
    inner: RefCell<BumpAllocatorImpl>,
}

// TODO: This is awful
unsafe impl Sync for BumpAllocator {}

unsafe impl GlobalAlloc for BumpAllocator {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        return self.inner.borrow_mut().alloc(layout);
    }

    unsafe fn dealloc(&self, ptr: *mut u8, layout: Layout) {
        return self.inner.borrow_mut().dealloc(ptr, layout);
    }
}

#[global_allocator]
static ALLOC8R: BumpAllocator = BumpAllocator {
    inner: RefCell::new(BumpAllocatorImpl {
        mem: [0u8; 4096],
        offset: 0,
    }),
};

#[alloc_error_handler]
fn alloc_error(layout: Layout) -> ! {
    panic!("Out of memory: {:?}", layout);
}

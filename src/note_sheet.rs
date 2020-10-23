#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct Note {
    pub on_time: f64,
    pub on_sample: ::std::os::raw::c_ulong,
    pub length_time: f64,
    pub length_sample: ::std::os::raw::c_uint,
    pub note: ::std::os::raw::c_int,
    pub freq: f64,
    pub loudness: f64,
}

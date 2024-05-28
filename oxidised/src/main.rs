use std::{env,fs};
const FNAME: &str = "../test/hosts";

fn main() {
    let mut args = env::args();
    let _ = args.next().expect("wtf");
    let host = args.next().expect("missing host");
    let ip = args.next().expect("missing ip");
    let tld = "htb";
    if env::args().len() != 3 {
        eprintln!("usage: update HOST IP");
        panic!("bad input");
    }
    let mut hosts = fs::read_to_string(FNAME).expect("file not found")
                    .lines()
                    .filter(|&l| !l.contains(tld))
                    .map(|s| s.to_string())
                    .collect::<Vec<String>>();
    hosts.push(format!("{}\t{}\n", &host[..], &ip[..]));
    dbg!(&hosts);
    fs::write(FNAME, hosts.join("\n")).expect("failed to write to file");
}

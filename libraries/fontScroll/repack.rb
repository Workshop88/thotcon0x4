require 'scanf'
File.open("font5x8.ino", mode: "r") { |f|
	f.each { |l|
		if(l =~ /^0x/)
			vals = Array.new
			l.scanf( "0x%2x," ) { |val|
				vals <<= val
			}
			puts "{"
			vals.reverse.each { |elem|
				puts "\t0b" + format("%08b", ((~(elem[0])) & 0xff) ).reverse + ","
			}
			puts "},"
		end
	}
}
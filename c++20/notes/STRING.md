### STRING 

* escape sequence: \", \\ 
* std::endl vs "\n": \n moves to the next line, but donot flush the buffer. 
* endl may be worse in performance. 
* At the program startup three text streams are predefined and need not be opened explicitly. stdin, stdout, stderr
* As initially opened, stderr stream is not fully buffered, stdin & stdout are fully buffered iff the stream can be determined not to refer to an interactive device.

 

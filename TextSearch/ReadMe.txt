This package provides a function putFile(...) to enqueue fully qualified file name inputs 
and creates a thread used to dequeue filenames and search for a specified string.
If a file contains the specified string its fully qualified filename is enqueued for output,
and then attempts to dequeue another filename.
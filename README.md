# dsearch
File duplicates scanner. 
## Usage
```
dsearch [Options]

Options:
  -h,--help                   Print this help message and exit
  -d,--directory TEXT         Root directory for search; default: cwd
  -a,--algorithms TEXT ...    Search algorithms: name, size, head, hash; default: 'name size head hash'
    name - compares file name
    size - compares file size
    head - compares only first 4096 bytes file block
    hash - compares whole file hashes
```
Example:
``` bash
dsearch -d /path/to/root -a 'name size'
```
## Info
* Contains docker file for build evironment.
* catch2 https://github.com/catchorg/Catch2
* cli11 https://github.com/CLIUtils/CLI11
* xxhash https://github.com/Cyan4973/xxHash

## Docker commands
* Build
``` bash
./docker.sh build
```
* Run tests
``` bash
./docker.sh test_run
```

#!/bin/env python

import subprocess
import sys

if '-f' not in sys.argv:
    print(
'''Usage:
  c2asm.py -f c-file [-C compiler-arguments] > out-file
  Converts C program into equivalent C file with code
  returned by assembler `gcc -S c-file`
Example:
  `./c2asm.py -f a.c -C "-march=native -O3" > b.c`
  will convert `a.c` file to `b.c` file with
  additional compiler arguments `-march=native` and
  `-O3`''')
    sys.exit(1)

compiler = 'gcc'

args = sys.argv[sys.argv[0] == __file__ :]

prog = args[1 + args.index('-f')]
comp_args = (args[1 + args.index('-C')]
             if '-C' in args else '')

cmd = ([compiler, prog, '-S', '-o', '-']
          + comp_args.split())
run = subprocess.run(cmd, capture_output=True)

out = str(run.stdout, 'utf-8')
out = out.split('\n')
def f(x):
    x = repr(x)[1:-1]
    return '"' + x.replace('"', '\\"') + '"'
out = map(lambda x: '{}'.format(f(x+'\n')), out)
out = '\n'.join(out)
out = '__asm__(\n{}\n);'.format(out)

sys.stderr.buffer.write(run.stderr)
print(out)

sys.exit(run.returncode)


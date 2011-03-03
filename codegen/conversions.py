# -*- coding: iso-8859-1 -*-
from util import *

import structures

import data

c = {int:'int', str:'char*', float:'float', bool:'int', chr:'char'}
cpp = {int:'int', str:'string', float:'float', bool:'int', chr:'char'}
java = {int:'int', str:'String', float:'float', bool:'int', chr:'char'}
CS = java
python = {int:'c_int', str:'c_char_p', float:'c_float', bool:'c_int', chr:'c_char'}
server = {int:'int', str:'str', float:'float', bool:'int', chr:'char'}

for i in members(data):
    if isinstance(i, structures.Model):
      c[i] = '_' + i.name + '*' 
      java[i] = 'Pointer'
      python[i] = 'c_void_p'
      server[i] = 'int'


print c
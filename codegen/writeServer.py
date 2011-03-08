# -*- coding: iso-8859-1 -*-
from mako.template import Template
from mako import exceptions
import glob

import structures
import conversions
import util

def write(data):
  data['conversions'] = conversions.server
  data['capitalize'] = util.capitalize
  data['lowercase'] = util.lowercase
  data['Model'] = structures.Model
  for file in glob.glob('templates/server/files/*.txt') + glob.glob('templates/server/files/game_app/*.txt'):
    writeFile(file[23:-4], data)

def writeFile(name, data):
  try:
    template = Template(filename='templates/server/files/%s.txt' % name)
    output = file('output/server/%s' % name, 'w')
    output.write(template.render(**data))
    output.close()
  except:
    print exceptions.text_error_template().render()

if __name__ == '__main__':
  write({})

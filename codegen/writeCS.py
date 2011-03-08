# -*- coding: iso-8859-1 -*-
from mako.template import Template
from mako import exceptions
import glob

import structures
import conversions
import util

def write(data):
  data['conversions'] = conversions.CS
  data['capitalize'] = util.capitalize
  data['lowercase'] = util.lowercase
  data['Model'] = structures.Model
  for file in glob.glob('templates/CS/files/*.txt'):
    writeFile(file[19:-4], data) #file[18:-4] should strip the templates/c/files/ and .txt
  for model in data['models']:
    data['model'] = model
    writeModel(data)

def writeFile(name, data):
  try:
    
    template = Template(filename='templates/CS/files/%s.txt' % name)
    output = file('output/CS/%s' % name, 'w')
    output.write(template.render(**data))
    output.close()
  except:
    print exceptions.text_error_template().render()

def writeModel(data):
  try:
    template = Template(filename='templates/CS/model.txt')
    output = file('output/CS/%s.CS' % data['model'].name, 'w')
    output.write(template.render(**data))
    output.close()
  except:
    print exceptions.text_error_template().render()


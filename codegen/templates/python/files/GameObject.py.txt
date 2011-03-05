# -*- python -*-

from library import library

from ExistentialError import ExistentialError

class GameObject(object):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration

% for model in models:

#\
#${model.doc}
%   if model.parent:
class ${model.name}(${model.parent.name}):
%   else:
class ${model.name}(GameObject):
%   endif
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.${lowercase(model.name)}GetId(ptr)

%   if model.type == 'Model':
  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.${lowercase(model.plural)}:
      if i.id == self.id:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
%   endif
%  for func in model.functions + model.properties:
  #\
#${func.doc}
  def ${func.name}(self\
%    for arg in func.arguments:
, ${arg.name}\
%    endfor
):
    self.validify()
%    for arg in func.arguments:
%      if isinstance(arg.type, Model):
    if not isinstance(${arg.name}, ${arg.type.name}):
      raise TypeError('${arg.name} should be of [${arg.type.name}]')
    ${arg.name}.validify()
%      endif
%    endfor
    return library.${lowercase(model.name)}${capitalize(func.name)}(self.ptr\
%    for arg in func.arguments:
%      if not isinstance(arg.type, Model):
, ${arg.name}\
%      else:
, ${arg.name}.ptr\
%      endif
%    endfor
)

%  endfor
%  for datum in model.data:
  #\
#${datum.doc}
  def get${capitalize(datum.name)}(self):
    self.validify()
    return library.${lowercase(model.name)}Get${capitalize(datum.name)}(self.ptr)

%  endfor

  def __str__(self):
    self.validify()
    ret = ""
%  for datum in model.data:
    ret += "${datum.name}: %s\n" % self.get${capitalize(datum.name)}()
%  endfor
    return ret
% endfor

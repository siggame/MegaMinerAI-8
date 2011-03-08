% for model in models:
class ${model.name}\
%   if model.parent:
(${model.parent.name})\
%   endif
:
  def __init__(self, game\
%   for datum in model.data:
, ${datum.name}\
%   endfor
):
    self.game = game
%   for datum in model.data:
    self.${datum.name} = ${datum.name}
%   endfor

  def toList(self):
    value = [
%   for datum in model.data:
      self.${datum.name},
%   endfor
      ]
    return value

  def nextTurn(self):
    pass

%   for func in model.functions:
  def ${func.name}(self\
%     for arg in func.arguments:
, ${arg.name}\
%     endfor
):
    pass

%   endfor

%   for prop in model.properties:
  def ${prop.name}(self\
%     for arg in prop.arguments:
, ${arg.name}\
%     endfor
):
    pass

%   endfor

% endfor

using System;
using System.Runtime.InteropServices;


///${model.doc}
public \
% if model.type == 'virtual':
abstract \
% endif
class ${model.name}\
% if model.parent:
: ${model.parent.name} \
% endif

{
% if not model.parent:
  public IntPtr ptr;
  protected int ID;
  protected int iteration;
%endif
  
  public ${model.name}()
  {
  }
  
  public ${model.name}(IntPtr p)
  {
    ptr = p;
    ID = Client.${lowercase(model.name)}GetId(ptr);
    iteration = BaseAI.iteration;
  }

  public \
% if model.type == 'virtual':
abstract \
%endif
% if model.parent:
override \
% endif
% if model.type == 'virtual':
bool validify();
%else:
bool validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.${lowercase(model.plural)}.Length; i++)
    {
      if(BaseAI.${lowercase(model.plural)}[i].ID == ID)
      {
        ptr = BaseAI.${lowercase(model.plural)}[i].ptr;
        iteration = BaseAI.iteration;
        return true;
      }
    }
    throw new ExistentialError();
  }
% endif
    
    //commands
    
% for func in model.functions:
  ///${func.doc}
%   if model.parent and func in model.parent.functions:
  public new int ${func.name}(\
%   else:
  public int ${func.name}(\
%   endif
%   for arg in func.arguments:
%     if func.arguments[0] is not arg:
, \
%     endif
%     if isinstance(arg.type, Model):
${arg.type.name} ${arg.name}\
%     else:
${conversions[arg.type]} ${arg.name}\
%     endif
%   endfor
)
  {
    validify();
%   for arg in func.arguments:
%     if isinstance(arg.type, Model):
    ${arg.name}.validify();
%     endif
%   endfor
    return Client.${lowercase(model.name)}${capitalize(func.name)}(ptr\
%   for arg in func.arguments:
, \
%     if isinstance(arg.type, Model):
${arg.name}.ptr\
%     else:
${arg.name}\
%     endif
%   endfor
);
  }
% endfor
    
    //getters
    
% for datum in model.data:
  ///${datum.doc}
  public \
%   if model.parent and datum in model.parent.data:
new \
%   endif
${conversions[datum.type]} get${capitalize(datum.name)}()
  {
    validify();
    return Client.${lowercase(model.name)}Get${capitalize(datum.name)}(ptr);
  }
% endfor

% for prop in model.properties:
   ///${prop.doc}
%     if isinstance(arg.type, Model):
  int \
%     else:
  ${conversions[arg.type]} \
%     endif
get${capitalize(prop.name)}(\
%   for arg in prop.arguments:
%     if prop.arguments[0] != arg:
, \
%     endif
%     if isinstance(arg.type, Model):
${arg.type.name}& ${arg.name}\
%     else:
${conversions[arg.type]} ${arg.name}\
%     endif
%   endfor
)
  {
    validify();
    return Client.${model.name.lower()}${capitalize(prop.name)}(ptr\
%   for arg in prop.arguments:
%     if isinstance(arg.type, Model):
, (_${arg.type.name}*) ${arg.name}.ptr\
%     else:
, ${arg.name}\
%     endif
%   endfor
);
  }

%   endfor
}

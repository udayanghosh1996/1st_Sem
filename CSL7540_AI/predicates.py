
def get_list_of_charaters(formula):
    return list(formula)
def put_open_paranthesis(formula):
    count=0
    p=0
    for i in range(len(formula)-1,-1,-1):
        #print(formula[i], i, count)
        if formula[i]==')':
            count+=1
        if formula[i]=='(':
            count-=1
        if count==0:
            formula.insert(i,'(')
            break
    #print(formula)
    return formula
def put_close_paranthesis(formula):
    count=0
    for i in range(0,len(formula)):
        if formula[i]=='(':
            count+=1
        if formula[i]==')':
            count-=1
        if count==0:
            if formula[i]=='!':
                    while not formula[i].isalpha():
                        i+=1
            if i!=(len(formula)-1):
                formula.insert(i+1,')')
            else:
                formula.append(')')
            break
    #print(formula)
    return formula
def check_wellform(formula):
    #print(formula)
    for i in range (0,len(formula)-1):
        if formula[0]==')':
            #print("returning from 1st loop 1st if")
            return False
        if formula[i]==')' and formula[i+1]=='(':
            #print("returning from 1st loop 2nd if")
            return False
    symbol=get_list_of_charaters("&|>~(")
    symbol1=get_list_of_charaters("&|>~)")
    for i in range (1,len(formula)):
        if formula[i]=='(' and symbol.count(formula[i-1])==0:
            #print("returning from 2nd loop")
            return False
    for i in range(0, len(formula)-1):

        if formula[i]==')' and symbol1.count(formula[i+1])==0:
            #print("returning from 3rd loop")
            return False
    return True
def perform_not_operation(formula):
    if check_wellform(formula)==False:
        #print("false in not")
        return None
    if formula[-1]!='!':
        new_formula=[]
        for i in range (0,len(formula)):
            if formula[i]=='!':
                if formula[i+1]!='&' and formula[i+1]!='|' and formula[i+1]!='>' and formula[i+1]!='~'and formula[i+1]!=')':
                    new_formula.append(formula[i])
                    i+=1
                    new_formula=put_open_paranthesis(new_formula)
                    #print(new_formula)
                    z=put_close_paranthesis(formula[i:len(formula)])
                    #print(z)
                    i=i+len(formula[i:len(formula)])
                    for ele in z:
                        new_formula.append(ele)
                    if i==len(formula):
                        break
                else:
                    return None
            else:
                new_formula.append(formula[i])
        return new_formula
    else:
        return None
def perform_and_operation(formula):
    if check_wellform(formula)==False:
        #print("false in and")
        return None
    if formula[0]!='&' or formula[-1]!='&':
        if formula.count('&')==1 and formula.count('|')==0 and formula.count('>')==0 and formula.count('~')==0:
            return formula
        new_formula=[]
        for i in range (0,len(formula)):
            if formula[i]=='&':
                if formula[i+1]!='!' and formula[i+1]!='&' and formula[i+1]!='|' and formula[i+1]!='>' and formula[i+1]!='~'and formula[i+1]!=')':
                    new_formula=put_open_paranthesis(new_formula)
                    new_formula.append(formula[i])
                    i=i+1
                    z=put_close_paranthesis(formula[i:len(formula)])
                    i=i+len(formula[i:len(formula)])
                    for ele in z:
                        new_formula.append(ele)
                    if new_formula[i]=='&':
                        return None
                    if i==len(formula):
                        break
                else:
                    return None
            else:
                new_formula.append(formula[i])
        return new_formula
    else:
        return None
def perform_or_operation(formula):
    if check_wellform(formula)==False:
        #print("false in or")
        return None
    if formula[0]!='|' or formula[-1]!='|':
        if formula.count('|')==1 and formula.count('>')==0 and formula.count('~')==0:
            return formula
        new_formula=[]
        for i in range (0,len(formula)):
            if formula[i]=='|':
                if formula[i+1]!='!' and formula[i+1]!='&' and formula[i+1]!='|' and formula[i+1]!='>' and formula[i+1]!='~'and formula[i+1]!=')':
                    new_formula=put_open_paranthesis(new_formula)
                    new_formula.append(formula[i])
                    i=i+1
                    z=put_close_paranthesis(formula[i:len(formula)])
                    i=i+len(formula[i:len(formula)])
                    for ele in z:
                        new_formula.append(ele)
                    if new_formula[i]=='|':
                        return None
                    if i==len(formula):
                        break
                else:
                    return None
            else:
                new_formula.append(formula[i])
        return new_formula
    else:
        return None
def perform_implication_operation(formula):
    if check_wellform(formula)==False:
        #print("false in implication")
        return None
    if formula[0]!='>' or formula[-1]!='>':
        if formula.count('>')==1 and formula.count('~')==0:
            return formula
        new_formula=[]
        for i in range (0,len(formula)):
            if formula[i]=='>':
                if formula[i+1]!='!' and formula[i+1]!='&' and formula[i+1]!='|' and formula[i+1]!='>' and formula[i+1]!='~'and formula[i+1]!=')':
                    new_formula=put_open_paranthesis(new_formula)
                    new_formula.append(formula[i])
                    i=i+1
                    z=put_close_paranthesis(formula[i:len(formula)])
                    i=i+len(formula[i:len(formula)])
                    for ele in z:
                        new_formula.append(ele)
                    if new_formula[i]=='>':
                        return None
                    if i==len(formula):
                        break
                else:
                    return None
            else:
                new_formula.append(formula[i])
        return new_formula
    else:
        return None
def perform_bidirectional_operation(formula):
    if check_wellform(formula)==False:
        #print("false in bidirectional")
        return None
    if formula[0]!='~' or formula[-1]!='~':
        if formula.count('~')==1:
            return formula
        new_formula=[]
        for i in range (0,len(formula)):
            if formula[i]=='~':
                if formula[i+1]!='!' and formula[i+1]!='&' and formula[i+1]!='|' and formula[i+1]!='>' and formula[i+1]!='~'and formula[i+1]!=')':
                    new_formula=put_open_paranthesis(new_formula)
                    new_formula.append(formula[i])
                    i=i+1
                    z=put_close_paranthesis(formula[i:len(formula)])
                    i=i+len(formula[i:len(formula)])
                    for ele in z:
                        new_formula.append(ele)
                    if new_formula[i]=='~':
                        return None
                    if i==len(formula):
                        break
                else:
                    return None
            else:
                new_formula.append(formula[i])
        return new_formula
    else:
        return None
if __name__=="__main__":
    formula=input("Enter the formula\n")
    formula_list=get_list_of_charaters(formula)
    NoneType=type(None)
    for i in range(0,5):
        if i==0:
            new_formula=perform_not_operation(formula_list)
        if i==1 and type(new_formula)!=NoneType:
            new_formula=perform_and_operation(new_formula)
        if i==2 and type(new_formula)!=NoneType:
            new_formula=perform_or_operation(new_formula)
        if i==3 and type(new_formula)!=NoneType:
            new_formula=perform_implication_operation(new_formula)
        if i==4 and type(new_formula)!=NoneType:
            new_formula=perform_bidirectional_operation(new_formula)
    if type(new_formula)!=NoneType:
        print(''.join(new_formula))
    else:
        print("Not well formed formula")
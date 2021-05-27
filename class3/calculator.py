#! /usr/bin/python3
from collections import deque
def read_number(line, index):
  number = 0
  while index < len(line) and line[index].isdigit():
    number = number * 10 + int(line[index])
    index += 1
  if index < len(line) and line[index] == '.':
    index += 1
    decimal = 0.1
    while index < len(line) and line[index].isdigit():
      number += int(line[index]) * decimal
      decimal /= 10
      index += 1
  token = {'type': 'NUMBER', 'number': number}
  return token, index


def read_plus(line, index):
  token = {'type': 'PLUS'}
  return token, index + 1


def read_minus(line, index):
  token = {'type': 'MINUS'}
  return token, index + 1


def read_times(line, index):
  token = {'type': 'TIMES'}
  return token, index + 1


def read_divider(line, index):
  token = {'type': 'DIVIDER'}
  return token, index + 1


def read_open_bracket(line, index):
  token = {'type': 'OPEN'}
  return token, index + 1


def read_close_bracket(line, index):
  token = {'type': 'CLOSE'}
  return token, index + 1


def tokenize(line):
  tokens = []
  index = 0
  while index < len(line):
    if line[index].isdigit():
      (token, index) = read_number(line, index)
    elif line[index] == '+':
      (token, index) = read_plus(line, index)
    elif line[index] == '-':
      (token, index) = read_minus(line, index)
    elif line[index] == '*':
      (token, index) = read_times(line, index)
    elif line[index] == '/':
      (token, index) = read_divider(line, index)
    elif line[index] == '(':
      (token, index) = read_open_bracket(line, index)
    elif line[index] == ')':
      (token, index) = read_close_bracket(line, index)
    else:
      print('Invalid character found: ' + line[index])
      exit(1)
    tokens.append(token)
  tokens.insert(0, {'type': 'OPEN'})
  tokens.append({'type': 'CLOSE'})
  return tokens


def evaluate_mult_div(tokens):
  new_tokens = []
  i=0
  while(i < len(tokens)):
    if tokens[i]['type'] == 'TIMES' or tokens[i]['type'] == 'DIVIDER':
      if tokens[i-1]['type'] != 'NUMBER' or tokens[i+1]['type'] != 'NUMBER':
        print('Invalid syntax')
        exit(1)
      if tokens[i]['type'] == 'DIVIDER' and tokens[i+1]['number'] == 0:
        print('Cannot be divided by zero')
        exit(1)
      
      if tokens[i]['type'] == 'TIMES':
        answer = new_tokens[-1]['number'] * tokens[i+1]['number']
      elif tokens[i]['type'] == 'DIVIDER':
        answer = new_tokens[-1]['number'] / tokens[i+1]['number']
      new_tokens[-1]['number'] = answer
      i += 1
    else:
      new_tokens.append(tokens[i])
    i += 1
  return new_tokens


def evaluate_plus_minus(tokens):
  answer = 0
  tokens.insert(0, {'type': 'PLUS'}) # Insert a dummy '+' token
  index = 1
  while index < len(tokens):
    if tokens[index]['type'] == 'NUMBER':
      if tokens[index - 1]['type'] == 'PLUS':
        answer += tokens[index]['number']
      elif tokens[index - 1]['type'] == 'MINUS':
        answer -= tokens[index]['number']
      else:
        print('Invalid syntax')
        exit(1)
    index += 1
  return answer


def evaluate(tokens):
  open_ids = deque([])
  inter_formula = []
  index = 0
  while index < len(tokens):
    if tokens[index]['type'] == 'OPEN':
      inter_formula.append(tokens[index])
      open_ids.append(len(inter_formula)-1)
    elif tokens[index]['type'] == 'CLOSE':
      open_id = open_ids.pop()
      partial_tokens = inter_formula[open_id+1:]

      inter_tokens = evaluate_mult_div(partial_tokens)
      answer = evaluate_plus_minus(inter_tokens)
      
      inter_formula[open_id]['type'] = 'NUMBER'
      inter_formula[open_id]['number'] = answer
      del inter_formula[open_id+1:]
    else:
      inter_formula.append(tokens[index])
    index += 1
  return inter_formula[0]['number']


def test(line):
  tokens = tokenize(line)
  actual_answer = evaluate(tokens)
  expected_answer = eval(line)
  if abs(actual_answer - expected_answer) < 1e-8:
    print("PASS! (%s = %f)" % (line, expected_answer))
  else:
    print("FAIL! (%s should be %f but was %f)" % (line, expected_answer, actual_answer))


# Add more tests to this function :)
def run_test():
  print("==== Test started! ====")
  test("1+2")
  test("2-1")
  test("1.0+2.1-3")
  test("1+2*3")
  test("1.0*3*0.2")
  test("1.0*3*0.2+1")
  test("1.0*3*0.2+2*3.5/5")
  test("3/1.0")
  test("(3+4*(2-1))/5")
  test("3*(1+2)*4+2*6/3")
  test("(3*4/2+5)-((14-3)/3-2)")
  test("(3*4/2+5)-((14-3)/3-2)+1.5")
  test("((14-3)/3-2)*2+1.5")
  print("==== Test finished! ====\n")
run_test()

while True:
  print('> ', end="")
  line = input()
  tokens = tokenize(line)
  answer = evaluate(tokens)
  print("answer = %f\n" % answer)
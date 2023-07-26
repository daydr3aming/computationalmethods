import re
import os

# Borrar HTML File si existe
if os.path.exists("output.html"):
  os.remove("output.html")

# Color de cada categoria lexica
styleFormat = {
  'reservedWords': 'color: #7DFF46',
  'operators': 'color: #F25656',
  'integer': 'color: #BA7ED7',
  'classes': 'color: cyan',
  'string': 'color: white',
  'comments': 'color: #615656',
  'variables': 'color: white',
  'stringLiteral': 'color: #FFE32F'
}

# Definición de Expresiones Regulares
reservedWords = re.compile(r'public |private |for |while |if |true |false |in |print|True|False') 
operators = re.compile(r'(\+|\-|\*|\/|\%|\=|\+=|\-=|\*=|\/=|\%=|\*\*=|\/\/=|\/\/|\(|\))') 
integerLiteral = re.compile(r'\b\d+\b') 
classes = re.compile(r'int|bool|complex|float|str')
# En Python, las palabras de clases sirven para convertir inputs a este tipo de dato, en vez de ser necesarios para declarar variables.
comments = re.compile(r'(#.*)') 
variables = re.compile(r'[a-zA-Z_][a-zA-Z0-9_]*')
stringLiteral = re.compile(r'"[^"]*"')


# Lexical Highlighter
def searchMatchLine(line):
  line = line.rstrip()
  matchLine = ''
  position = 0 # Iniciamos en 0
  for match in re.finditer(
      '|'.join([ #Agregamos todos los tipos de matches que podemos tener
        reservedWords.pattern, operators.pattern, integerLiteral.pattern, classes.pattern, comments.pattern,variables.pattern, stringLiteral.pattern
]), line):
    matchLine += line[position:match.start()]
    position = match.end()
    wordMatch = match.group()
  # Comparamos y Aasignamos, vemos todos los posibles matches de una palabra/símbolo/string
    if reservedWords.match(wordMatch): # Palabras Reservadas
      matchLine += f'<span style="{styleFormat["reservedWords"]}">{wordMatch}</span>'
    elif operators.match(wordMatch): # Operadores
      matchLine += f'<span style="{styleFormat["operators"]}">{wordMatch}</span>'
    elif integerLiteral.match(wordMatch): # Integers
      matchLine += f'<span style="{styleFormat["integer"]}">{wordMatch}</span>'
    elif classes.match(wordMatch): # Tipos de Dato
      matchLine += f'<span style="{styleFormat["classes"]}">{wordMatch}</span>'
    elif comments.match(wordMatch): # Comentarios
      matchLine += f'<span style="{styleFormat["comments"]}">{wordMatch}</span>'
    elif variables.match(wordMatch): # Variables
      matchLine += f'<span style="{styleFormat["variables"]}">{wordMatch}</span>'
    elif stringLiteral.match(wordMatch):
      matchLine += f'<span style="{styleFormat["stringLiteral"]}">{wordMatch}</span>'
      
  matchLine += line[position:]
  return matchLine


# Leer archivo de código
with open('entrada.txt', 'r') as readFile:
  code = readFile.read()

# Guarda contenidos de la file en una lista
lexicalHighlighter = []
for line in code.split('\n'):
  lexicalHighlighter.append(searchMatchLine(line)) # Agregamos

# Archivo HTML formateado con spans que hacen el highlight.
with open('output.html', 'w') as file:
  file.write('<html>\n')
  file.write('<head>\n')
  file.write('<link rel="stylesheet" type="text/css">')
  file.write('<style>\n')
  for style in styleFormat:
    file.write(f'span[{style}]' + '{' + styleFormat[style] + '}\n')
  file.write('</style>\n')
  file.write('</head>\n')
  file.write('<body style = "background-color: #2E2E2E";>\n')
  for line in lexicalHighlighter:
    file.write(f'<p style = "font-size: 20px; font-family: \'Cascadia Code\', sans-serif;">{line}</p>\n')
  file.write('</body>\n')
  file.write('</html>\n')
readFile.close()
file.close

print('''
Lexical Highlighter
--------------------
created by:
Fernanda Romo
Rogelio Guzman
--------------------
HTML file "output.html" created.
''')


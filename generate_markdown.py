import os

md = open('integrated.md', mode='w', encoding='utf-8')
files = os.listdir()
for fname in files:
    if(fname.endswith('.cpp') or fname.endswith('.hpp')):
        md.write(fname+'\n\n')
        md.write('```c++\n')
        with open(fname, mode='r', encoding='utf-8') as cur:
            while(line := cur.readline()):
                md.write(line)
        md.write('```\n\n')
md.close()

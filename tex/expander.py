import os, sys
from typing import List
import argparse
import urllib.request

targetExt = [".cpp", ".hpp"]
template = "./template.tex"
outputFileName = "main.tex"

def output(targetFile: str, outDir: str) -> str:
    '''
    Recieve target file and copy to outDir.
    Return output filename.
    '''
    with open(targetFile, "r") as f:
        lines = f.read()
    outTexFile = targetFile.replace(os.sep, "##") + ".tex"
    title = os.path.basename(targetFile).replace("_", "\\_")
    with open(os.path.join(outDir, outTexFile), "w") as g:
        g.write(f"\\section*{{{title}}}\n")
        g.write("\\begin{lstlisting}\n")
        g.write(lines)
        g.write("\\end{lstlisting}\n")
    
    return outTexFile

def dfs(dirName: str, outDir: str, dorecursive: bool) -> List[str]:
    '''
    Search directories recursively.
    Return list of output filenames
    '''
    outFiles = []
    for dir in os.listdir(dirName):
        name = os.path.join(dirName, dir)
        if dorecursive and os.path.isdir(name):
            outFiles.extend(dfs(name, outDir,  dorecursive))
        else:
            if os.path.splitext(dir)[1] in targetExt:
                outFiles.append(output(name, outDir))
    return outFiles

def main(dirNames: List[str], output="out", recursive=False):
    # check if directories exits
    for d in dirNames:
        if not os.path.exists(d):
            print(f"[Error] No such file or directory '{d}'", file=sys.stderr)
            sys.exit(1)

    # make outputfile
    if not os.path.exists(output):
        os.mkdir(output)
    
    # search files
    outFiles = []
    for d in dirNames:
        outFiles.extend(dfs(d, output, recursive))

    # download plistings package
    plistings = os.path.join(output, "plistings.sty")
    urllib.request.urlretrieve("https://raw.githubusercontent.com/h-kitagawa/plistings/master/plistings.sty",
                               plistings)

    # write main file
    with open(os.path.join(output, outputFileName), "w") as f:
        with open(template, "r") as g:
            f.write(g.read())
        f.write("\\begin{document}\n")
        for i in outFiles:
            f.write(f"\\input{{{i}}}\n")
            f.write("\\newpage\n")
        f.write("\\end{document}\n")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("dirName", type=str, nargs="+",
                        help="target directory names")
    parser.add_argument("-o", "--output", default="./out", nargs=1,
                        help="output directory name")
    parser.add_argument("-r" , "--recursive", action="store_true",
                        help="search recursively")
    args = parser.parse_args()

    main(args.dirName, args.output, args.recursive)

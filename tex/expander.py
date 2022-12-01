import os
from typing import List
import argparse
import urllib.request
import logging
import bz2

targetExt = {".cpp": "C++", ".hpp": "C++",
             ".sh": "bash", ".py": "Python"}  # target extensions
# path of the directory which has this file
expanderDir = os.path.dirname(__file__)
# path of template latex file
template = os.path.join(expanderDir, "template.tex")
outputFileName = "main.tex"  # output filename


def output(targetFile: str, outDir: str, lang: str) -> str:
    '''
    Recieve target file and copy to outDir.
    Return output filename.
    '''
    with open(targetFile, "r") as f:
        logging.info(f"Open {targetFile}")
        lines = f.read()
    outTexFile = targetFile.replace(os.sep, "##") + ".tex"
    title = os.path.basename(targetFile).replace("_", "\\_")
    outFile = os.path.join(outDir, outTexFile)
    with open(outFile, "w") as g:
        g.write(f"\\section*{{{title}}}\n")
        g.write(f"\\begin{{lstlisting}}[language={lang}]\n")
        g.write(lines)
        g.write("\\end{lstlisting}\n")
        g.write("\\newpage\n")
        logging.info(f"Write {outFile}")

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
            extension = os.path.splitext(dir)[1]
            if extension in targetExt:
                outFiles.append(output(name, outDir, targetExt[extension]))
    return outFiles


def main(dirNames: List[str], output="out", recursive=False):

    # make outputfile
    if not os.path.exists(output):
        os.mkdir(output)
        logging.info(f"made {output}")

    # search files
    outFiles = []
    for d in dirNames:
        outFiles.extend(dfs(d, output, recursive))

    # download jlisting package
    jlistingPath = os.path.join(output, "jlisting.sty")
    with open(jlistingPath, 'w') as f:
        with urllib.request.urlopen("https://ymu.dl.osdn.jp/mytexpert/26068/jlisting.sty.bz2") as ur:
            f.write(bz2.decompress(ur.read()).decode("utf-8"))

    # write main file
    with open(os.path.join(output, outputFileName), "w") as f:
        with open(template, "r") as g:
            f.write(g.read())
        f.write("\\begin{document}\n")
        for i in outFiles:
            f.write(f"\\input{{{i}}}\n")
        f.write("\\end{document}\n")
    logging.info(f"Write {os.path.join(output, outputFileName)}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("dirName", type=str, nargs="+",
                        help="target directory names")
    parser.add_argument("-o", "--output", default=os.path.join(expanderDir, "out"), type=str,
                        metavar="outDir",
                        help="output directory")
    parser.add_argument("-r", "--recursive", action="store_true",
                        help="search recursively flag")
    parser.add_argument("-l", "--log", action="store_true",
                        help="output log")
    args = parser.parse_args()

    if args.log:
        logging.basicConfig(
            format='[%(levelname)s] %(asctime)s %(message)s', level=logging.INFO,
            datefmt='%Y/%m/%d %I:%M:%S')

    main(args.dirName, args.output, args.recursive)

import os
import re
import ast
import argparse

fext = ".template"

def main():
    parser = argparse.ArgumentParser("Writing a file with template for "\
                                     "repetitive codes.")
    parser.add_argument("name", type=str,
        help="Name of a file or directory to be written.")
    parser.add_argument("-r", dest="isrecursive", action="store_const",
        const=True, default=False,
        help="If the name is a directory, then apply the conversion "\
             "recursively")
    args = parser.parse_args()

    # check if the name is a file
    if os.path.isfile(args.name):
        convert_file(args.name)
    elif os.path.isdir(args.name):
        fnames = get_all_files_with_ext(args.name, fext, args.isrecursive)
        for fname in fnames:
            convert_file(fname)
            newfname = get_newfname(fname)
            print("Writing template %s to %s" % (fname, newfname))

def convert_file(fname, normalize=True):
    # check the file name (it must end in ".template")
    if not fname.endswith(fext):
        raise RuntimeError("The file must end in %s" % fext)

    # read the original content
    with open(fname, "r") as f:
        content = f.read()

    # convert the content
    newcontent = convert_str(content)

    # normalization:
    # * only 1 blank lines at the end,
    # * no whitespaces in lines with no content
    if normalize:
        newcontent = normalize_str(newcontent)

    # write the new content to a new file
    newfname = get_newfname(fname)
    with open(newfname, "w") as f:
        f.write(newcontent)

def get_newfname(fname):
    return fname[:-len(fext)]

def convert_str(content):
    # construct the block pattern
    # groups:
    # 1: the block name
    # 2: the variables
    # 3: the string content
    end_pattern = r"/\*\*\s*end\s+\1\s*\*\*/"
    # the beginning pattern
    pattern = r"/\*\*\s*begin\s+(\w+)((?:[^\*]|\*(?=[^/]))+)\s*\*/"
    # the string content
    pattern += r"((?:[^/]|/(?!%s))*)" % end_pattern[1:]
    # the end pattern
    pattern += end_pattern

    # find the blocks
    res_all = re.finditer(pattern, content)

    newcontent = content
    for res in res_all:
        # parse the variables to get a dict of variables
        vars = parse_vars(res.group(2))
        newstr = substitute(res.group(3), vars)
        newcontent = newcontent.replace(res.group(0), newstr)

        # replace some blocks, if any
        newcontent = convert_str(newcontent)

    return newcontent

def parse_vars(var_str):
    # return the variables in a dictionary
    res = {}
    lenval = None

    # construct the variable pattern
    # groups:
    # 1: the variable name
    # 2: the variable values
    vpattern = r"\s*(\w+)\s*=\s*([^;]+)"
    vres_all = re.finditer(vpattern, var_str)
    for vres in vres_all:
        varname = vres.group(1)
        varvalues = ast.literal_eval(vres.group(2))

        # do the checkings
        # (1) the len of iterable values must be the same for all variables
        if lenval is None:
            lenval = len(varvalues)
        elif lenval != len(varvalues):
            raise RuntimeError("Variable '%s' length does not " \
                               "match the rest." % varname)

        # (2) the variable names cannot be duplicated in the same block
        if varname in res:
            raise RuntimeError("Duplicate variable: '%s'" % varname)

        # store the variable
        res[varname] = varvalues
    return res

def substitute(content, vars):
    if len(vars) == 0: return content

    lenvar = len(vars[list(vars.keys())[0]])
    contents = []
    for i in range(lenvar):
        s = content
        for varname in vars:
            s = s.replace("@%s@" % varname, vars[varname][i])
        contents.append(s)
    return "".join(contents)

def normalize_str(content):
    # remove the trailing whitespace,
    # add "\n" to the end of the file,
    newcontent = content.rstrip()
    newcontent = newcontent + "\n"

    # remove whitespaces in a line without content
    pattern = r"(^|\r*\n)\s*($|\r*\n)"
    repl = r"\1\2"
    newcontent = re.sub(pattern, repl, newcontent)
    return newcontent

def get_all_files_with_ext(fdir, fext, isrecursive):
    res = []
    dircontents = [os.path.join(fdir, c) for c in os.listdir(fdir)]
    for dircontent in dircontents:
        if os.path.isfile(dircontent) and dircontent.endswith(fext):
            res.append(dircontent)
        elif os.path.isdir(dircontent) and isrecursive:
            res += get_all_files_with_ext(dircontent, fext, isrecursive)
    return res

if __name__ == "__main__":
    main()

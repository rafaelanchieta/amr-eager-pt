# -*- coding: utf-8 -*-

import argparse
import os
import re
import string
import sys

from nltk import word_tokenize

from util import run_palavras, run_lxparser, run_corenlp, run_nlpnet


class Preprocessing(object):

    def __init__(self, amr_file):
        self.name = os.path.abspath(amr_file)
        self.amr = open(amr_file, 'r')
        self.regex_snt = r'# ::snt (.+)'

    def create_tokenized_sentences(self):
        sentences_file = open(self.name + '.sentences', 'w')
        for snt in self.amr.readlines():
            match = re.match(self.regex_snt, snt)
            if match:
                tr = str.maketrans("", "", string.punctuation)
                s = match.group(1).translate(tr)
                sentences_file.write(' '.join(word_tokenize(s)))
                sentences_file.write('\n')
        sentences_file.close()

    def create_out_file(self):
        sentences_file = open(self.name + '.sentences', 'r')
        out_file = open(self.name + '.out', 'w')
        constituents = run_lxparser.call_lxparser(self.name + '.sentences')
        cont_snt = 1
        cont_line = 0
        for line in sentences_file.readlines():
            out_file.write('Sentence #')
            out_file.write(str(cont_line + 1))
            out_file.write(' (')
            out_file.write(str(len(word_tokenize(line))))
            out_file.write(' tokens):')
            out_file.write('\n')
            out_file.write(line)
            print('Line: ', line)
            # tokens = run_palavras.call_palavras(line)
            tags = run_nlpnet.call_nlpnet(line)
            print('Tags: ', tags)
            for word, tag in tags:
                print(word, tag)
                out_file.write('[Text=')
                out_file.write(word)
                if cont_snt == 1:
                    out_file.write(' CharacterOffsetBegin=0 CharacterOffsetEnd=')
                    size = len(word)
                    out_file.write(str(size))
                    out_file.write(' PartOfSpeech=')
                    out_file.write(tag)
                    lemma = run_palavras.call_palavras(word)
                    print('Lemma: ', lemma)
                    out_file.write(' Lemma=')
                    out_file.write(lemma)
                    out_file.write(' NamedEntityTag=O]')
                    out_file.write('\n')
                    cont_snt += 1
                else:
                    out_file.write(' CharacterOffsetBegin=')
                    size += 1
                    out_file.write(str(size))
                    out_file.write(' CharacterOffsetEnd=')
                    size = size + len(word)
                    out_file.write(str(size))
                    out_file.write(' PartOfSpeech=')
                    out_file.write(tag)
                    out_file.write(' Lemma=')
                    lemma = run_palavras.call_palavras(word)
                    print('Lemma: ', lemma)
                    out_file.write(lemma)
                    out_file.write(' NamedEntityTag=O]')
                    out_file.write('\n')
            out_file.write(constituents[cont_line])
            out_file.write('\n')
            out_file.write(run_corenlp.call_corenlp(line))
            cont_line += 1
        out_file.close()


if __name__ == '__main__':
    argparser = argparse.ArgumentParser(description='Preprocessing DamonteAMR')
    argparser.add_argument('-f', '--file', help='Input file', required=True)
    try:
        args = argparser.parse_args()
    except:
        argparser.error('Invalid arguments')
        sys.exit()

    p = Preprocessing(args.file)
    p.create_tokenized_sentences()
    p.create_out_file()
    # run_palavras.call_palavras('viera')

import os, sys
from functools import lru_cache
from rich import print as pprint

"""
Simple python encrypter
"""


#TODO:Optimize performance


@lru_cache(maxsize=None)
def crypt(in_file:str, out_file:str, kword:str, k:int):
	fin 	=	open(in_file, 'rb').read()
	fout	=	open(out_file, 'wb+')

	kwlen = len(kword)
	bts, idx = len(fin), 0
	ret = b''
	kword = bytes(kword, 'utf8')

	for byte in fin:
		kpos = k % kwlen
		xord = bytes( [ byte ^ kword[kpos] ] )
		ret += xord
		print(F'\r{idx/bts*100.:F}%\r')
	
	fout.write()

	


pprint(os.getcwd())

if __name__ == "__main__":
	if len(sys.argv) != 5:
		pprint("Usage: python3 crypt.py INPUT_FILE(str) OUTPUT_FILE(str) KEYWORD(str) KEY(int)")

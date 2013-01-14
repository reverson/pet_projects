#!/usr/bin/python

import re
import urllib
import sys
import getopt


def download(argv):
  f = None
  url = None
  try:
    opts, args = getopt.getopt(argv, "f:u:", ["file=", "url="])
  except getopt.GetoptError:
    sys.exit(2)
  for opt, arg in opts:
    if opt in ("-f", "--file"):
      f = arg
    elif opt in ("-u", "--url"):
      url = arg

  if f is None:
    sys.exit(2)
  if url is None:
    sys.exit(2)
  t = open(f).read().split('\n')
  for i in t:
    r = re.search('"(.*>?)"', i)
    if r is not None:
      print url+r.groups()[0]
      urllib.urlretrieve (url+r.groups()[0], r.groups()[0])

if __name__ == "__main__":
  download (sys.argv[1:])

#! /usr/bin/env python
# encoding: utf-8

import os,sys,re
import TaskGen,Task
from Utils import quote_whitespace
from TaskGen import extension
EXT_WINRC=['.rc']
winrc_str='${WINRC} ${_CPPDEFFLAGS} ${_CCDEFFLAGS} ${WINRCFLAGS} ${_CPPINCFLAGS} ${_CCINCFLAGS} ${WINRC_TGT_F} ${TGT} ${WINRC_SRC_F} ${SRC}'
def rc_file(self,node):
	obj_ext='.rc.o'
	if self.env['WINRC_TGT_F']=='/fo':obj_ext='.res'
	rctask=self.create_task('winrc')
	rctask.set_inputs(node)
	rctask.set_outputs(node.change_ext(obj_ext))
	self.compiled_tasks.append(rctask)
Task.simple_task_type('winrc',winrc_str,color='BLUE',before='cc cxx',shell=False)
def detect(conf):
	v=conf.env
	winrc=v['WINRC']
	v['WINRC_TGT_F']='-o'
	v['WINRC_SRC_F']='-i'
	if not winrc:
		if v['CC_NAME']in['gcc','cc','g++','c++']:
			winrc=conf.find_program('windres',var='WINRC',path_list=v['PATH'])
		elif v['CC_NAME']=='msvc':
			winrc=conf.find_program('RC',var='WINRC',path_list=v['PATH'])
			v['WINRC_TGT_F']='/fo'
			v['WINRC_SRC_F']=''
	if not winrc:
		conf.fatal('winrc was not found!')
	v['WINRCFLAGS']=''

extension(EXT_WINRC)(rc_file)

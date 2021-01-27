TEMPLATE = subdirs

SUBDIRS += \
	CourseLib \
	Game \
	NysseUnitTest

CourseLib.subdir = Course/CourseLib
Game.depends = CourseLib

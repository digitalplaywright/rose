include $(top_srcdir)/config/Makefile.for.ROSE.includes.and.libs
include $(top_srcdir)/tests/input_codes/Makefile.for.input.codes

# Forward declarations
noinst_PROGRAMS =
TEST_TARGETS =

INCLUDES = $(ROSE_INCLUDES)
EXTRA_DIST = tests.conf

## Don't use the repository in ../src
CXX_TEMPLATE_REPOSITORY_PATH = .


# Tests the RangeMap class
noinst_PROGRAMS += testRangeMap
testRangeMap_SOURCES = testRangeMap.C
testRangeMap_LDADD = 
TEST_TARGETS += testRangeMap.passed
testRangeMap.passed: tests.conf testRangeMap
	@$(RTH_RUN) CMD=./testRangeMap $< $@

noinst_PROGRAMS += testFileNameClassifier
testFileNameClassifier_SOURCES = testFileNameClassifier.C
testFileNameClassifier_LDADD   = $(LIBS_WITH_RPATH) $(ROSE_LIBS)
if ROSE_BUILD_OS_IS_CYGWIN
# This test fails to run under Cygwin. [DQ 2009-03-21]
else
TEST_TARGETS += testFileNameClassifier.passed
endif
testFileNameClassifier.passed: tests.conf testFileNameClassifier
	@$(RTH_RUN) CMD=./testFileNameClassifier $< $@

# Tests the StringUtility functions
noinst_PROGRAMS += testStrings
testStrings_SOURCES = testStrings.C
testStrings_LDADD   = $(top_builddir)/src/util/stringSupport/libRoseStringSupport.la
TEST_TARGETS += testStrings.passed
testStrings.passed: tests.conf testStrings
	@$(RTH_RUN) CMD=./testStrings $< $@

# Test file name support
noinst_PROGRAMS += filenameSupport
filenameSupport_SOURCES = filenameSupport.C
filenameSupport_LDADD = $(top_builddir)/src/util/stringSupport/libRoseStringSupport.la
TEST_TARGETS += filenameSupport.passed
filenameSupport.passed: tests.conf filenameSupport
	@$(RTH_RUN) CMD=./filenameSupport $< $@

# Test for directory support (SgDirectory IR node)
noinst_PROGRAMS += directorySupport
directorySupport_SOURCES = directorySupport.C
directorySupport_LDADD = $(LIBS_WITH_RPATH) $(ROSE_LIBS)
TEST_TARGETS += directorySupport.passed
directorySupport.passed: tests.conf directorySupport $(__minimal_input_code)
	@$(RTH_RUN) CMD=./directorySupport ARGS="-c -rose:verbose 0 $(__minimal_input_code)" $< $@

check-local: $(TEST_TARGETS)

clean-local:
	rm -rf $(CXX_TEMPLATE_OBJECTS) Templates.DB ii_files ti_files
	rm -f rose_*.C *.dot
	rm -rf xxx_new_directory_node_support
	rm -f $(TEST_TARGETS) $(TEST_TARGETS:.passed=.failed)

distclean-local:
	rm -rf Templates.DB









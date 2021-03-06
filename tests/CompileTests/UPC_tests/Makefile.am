include $(top_srcdir)/config/Makefile.for.ROSE.includes.and.libs

#####################################################################################
# These are UPC testcodes targeting aspects of UPCC that might not be a subset of C #
#####################################################################################

# affinity &arr[i] is parsed to arr+i, may hurt the later translation
# sharedArrayInit.upc: Berkeley UPC compiler 1.6 does not support shared arrays with initializer
TESTCODES_REQUIRED_TO_PASS = \
   threads_in_expression.upc \
   barrier.upc \
   consistency.upc \
   hello.upc \
   fence.upc \
   forall_1.upc \
   forall_affinity.upc \
   forall_continue.upc \
   lock.upc \
   macro_names.upc \
   max_block_size.upc \
   mythread.upc \
   notify_wait.upc \
   restrict.upc \
   shared.upc \
   shared_2.upc \
   sharedArrayInit.upc \
   sharedInit.upc \
   strict.upc \
   threads.upc \
   threads_2.upc \
   typedef.upc \
   upc_all_alloc_ex.upc upc_all_broadcast_ex.upc \
   upc_all_lock_alloc_ex.upc upc_all_permute_ex.upc upc_all_prefix_reduceL_ex.upc \
   upc_all_reduceL_ex.upc upc_all_scatter_ex.upc \
   upc_all_exchange_ex_dynamic.upc upc_all_gather_all_ex_dynamic.upc \
   upc_all_gather_ex_dynamic.upc upc_all_scatter_ex_dynamic.upc \
   bupc_test.upc \
   istream.upc \
   test2010_01.upc \
   test2010_02.upc \
   test2011_01.upc \
   test2011_02.upc \
   test2011_03.upc \
   test2011_04.upc \
   test2011_05.upc \
   test2011_06.upc \
   test2011_07.upc \
   test2011_08.upc \
   test2011_09.upc \
   test2011_10.upc \
   test2011_11.upc \
   test2011_14.upc \
   static_upc_all_exchange_ex.upc \
   static_upc_all_gather_all_ex.upc \
   static_upc_all_gather_ex.upc \
   static_test2011_12.upc \
   static_test2011_13.upc

# upc_XXXsizeof() has two issues:
# 1. They are evaluated by EDG, operators are not preserved in EDG's IL
# 2. EDG 3.3 get wrong evaluation values,  EDG 3.10 fixes the bug though.
TESTCODE_CURRENTLY_FAILING = \
   sizeof.upc \
   sizeof_2.upc

#  test2011_08.upc

# Automake's testing mechanism (which defines the "make check" rule) requires passing tests.
TESTCODES = \
	 $(TESTCODES_REQUIRED_TO_PASS)

# QMTest allows both passing and failing tests.
ALL_TESTCODES = \
   $(TESTCODES) \
	 $(TESTCODE_CURRENTLY_FAILING)

# Liao (6/11/2008) --edg:upc and --edg:restrict are not required since ROSE can add them internally based on the file suffix (.upc) , no backend compilation since GCC does not recognize UPC .
if ROSE_USE_NEW_EDG_INTERFACE
# JJW (12/15/2008): Force C99 mode so we can have declarations in the initializers of forall statements
# ROSE_FLAGS = --edg:no_warnings -rose:skipfinalCompileStep --edg:upc --edg:c99
# ROSE_FLAGS = -rose:verbose 0 --edg:no_warnings -rose:exit_after_parser -rose:skipfinalCompileStep -rose:upc_threads 1
# ROSE_FLAGS = -rose:verbose 0 --edg:no_warnings -rose:exit_after_parser -rose:skipfinalCompileStep

# DQ (2/17/2011): Use "-rose:exit_after_parser" option to isolate the testing to just EDG
# (avoids ROSE bugs using new EDG 4.0 frontent (which is unfinished work)).  Use "--edg:c99"
# so that we can have declarations in the initializers of forall statements.
# Note that only upc_all_gather_ex.upc, upc_all_gather_all_ex.upc, and upc_all_exchange_ex.upc require the "-rose:upc_threads 1" option.
# ROSE_FLAGS = -rose:verbose 0 --edg:no_warnings --edg:c99 -rose:exit_after_parser -rose:skipfinalCompileStep -rose:upc_threads 1
# ROSE_FLAGS = -rose:verbose 0 --edg:no_warnings --edg:c99 -rose:exit_after_parser -rose:skipfinalCompileStep
ROSE_FLAGS = -rose:verbose 0 --edg:no_warnings --edg:c99 -rose:skipfinalCompileStep
else
# ROSE_FLAGS = --edg:no_warnings -rose:skipfinalCompileStep --edg:upc
# ROSE_FLAGS = -rose:verbose 0 --edg:no_warnings -rose:exit_after_parser -rose:skipfinalCompileStep -rose:upc_threads 1
# ROSE_FLAGS = -rose:verbose 0 --edg:no_warnings -rose:exit_after_parser -rose:skipfinalCompileStep
ROSE_FLAGS = -rose:verbose 0 --edg:no_warnings -rose:skipfinalCompileStep
endif
#ROSE_FLAGS = --edg:no_warnings -w --edg:restrict --edg:upc -rose:verbose 3

PASSING_TEST_Output = $(addprefix rose_,${TESTCODES})
TEST_Output = $(addprefix rose_,${ALL_TESTCODES})

rose_static_%: $(srcdir)/static_% ../../testTranslator
	../../testTranslator -rose:UPC $(ROSE_FLAGS) -rose:upc_threads 1 -c $< -o $@

rose_%: $(srcdir)/% ../../testTranslator
	../../testTranslator -rose:UPC $(ROSE_FLAGS) -rose:upc_threads 1 -c $< -o $@


# $(TEST_Output): ../../testTranslator $(srcdir)/$(@:rose_%=%)
# ../../testTranslator -rose:UPC $(ROSE_FLAGS) -c $(srcdir)/$(@:rose_%=%)
../../testTranslator:
	cd ../..; $(MAKE) testTranslator

# DQ (2/3/2011): Note that all but test2004_22.upc can also be compiled as UPC instead of UPC++ testcodes.
# DQ (9/19/2010): Separated this UPC++ test out from the UPC tests. This test code simply uses some C++ specific
# constructs and does not represent any special work to build UPC++ work. Basically just UPC that allows C++ code.
UPCXX_TESTCODES = \
   test2004_22.upc \
   test2011_01.upc \
   test2011_03.upc \
   test2011_04.upc \
   test2011_05.upc \
   test2011_06.upc \
   test2011_07.upc

FAILING_UPCXX_TESTCODES = \
   test2011_02.upc


UPCXX_TEST_Objects = ${UPCXX_TESTCODES:.upc=.o}

# $(UPCXX_TEST_Objects): ../../testTranslator $(srcdir)/$(@:.o=.c)
$(UPCXX_TEST_Objects): ../../testTranslator $(srcdir)/$(@:.o=.c)
	../../testTranslator -rose:UPCxx $(ROSE_FLAGS) -rose:upc_threads 1 -c $(srcdir)/$(@:.o=.upc)


# DQ (2/4/2011): Added test for UPC keyword "THREADS". It is only present when "-rose:upc_threads" option is not used.
testForUpcThreadsKeywordInGeneratedCode: rose_threads.upc
	rm -f rose_threads.upc
	../../testTranslator -rose:UPC -rose:verbose 0 --edg:no_warnings -rose:skipfinalCompileStep -c $(srcdir)/threads.upc
	@echo "Testing for use of THREADS upc keyword in generated code."
	@grep "There are %d threads" rose_threads.upc
	grep "There are %d threads" rose_threads.upc | grep "THREADS"

# DQ (2/4/2011): Added test for UPC keyword "MYTHREAD".
testForUpcMythreadKeywordInGeneratedCode: rose_mythread.upc
	rm -f rose_mythread.upc
	../../testTranslator -rose:UPC -rose:verbose 0 --edg:no_warnings -rose:skipfinalCompileStep -c $(srcdir)/mythread.upc
	@echo "Testing for use of MYTHREAD upc keyword in generated code."
	@grep "I am thread:" rose_mythread.upc
	grep "I am thread:" rose_mythread.upc | grep "MYTHREAD"

rose_shared.upc.aa:rose_shared.upc
	split -36 rose_shared.upc rose_shared.upc.
	test -f rose_shared.upc.aa
	test -f rose_shared.upc.ab

QMTEST_Objects = ${ALL_TESTCODES:.upc=.qmt}

# Make rule to build the QMTest database files
CURRENT_DIRECTORY = `pwd`
$(QMTEST_Objects): ../../testTranslator $(srcdir)/$(@:.qmt=.upc)
	@echo "Calling QMTEST_Objects rule: "
	qm.sh f rose.RoseTest $(CURRENT_DIRECTORY)/../../testTranslator NULL $(ROSE_FLAGS) -c $(srcdir)/$(@:.qmt=.upc)

# Include makefile rules specific to QMTest
include $(top_srcdir)/config/QMTest_makefile.inc

# DQ (9/17/2010): Added more test code, but not yet used in internal tests.
# DQ (9/15/2010): Moved UPC standard header files to be included automatically (moved to the ROSE compiler include directory).
# put the headers here for now. TODO: Move them to a better place
# EXTRA_DIST = $(ALL_TESTCODES) upc.h upc_relaxed.h upc_strict.h upc_collective.h
  EXTRA_DIST = $(ALL_TESTCODES)  $(UPCXX_TESTCODES)

check-local:
	@echo "Tests for UPC examples."
	@$(MAKE) $(PASSING_TEST_Output)
	@$(MAKE) rose_shared.upc.aa
if !ROSE_USE_NEW_EDG_INTERFACE
	@echo "Tests for UPC++ examples."
	@$(MAKE) $(UPCXX_TEST_Objects)
else
	@echo "Skipping testing UPC++ test codes with new EDG (--upc++ mode not yet added in EDG 4.0; ROSE specific feature)."
endif
#	DQ (2/5/2011): This failed for a very few Hudson tests, but they are not critical
#	tests so I will eliminate them for now. I don't know why they failed.
#	@$(MAKE) testForUpcThreadsKeywordInGeneratedCode
#	@$(MAKE) testForUpcMythreadKeywordInGeneratedCode
	@echo "***********************************************************************************************"
	@echo "****** ROSE/tests/CompileTests/UPC_tests: make check rule complete (terminated normally) ******"
	@echo "***********************************************************************************************"

clean-local:
	rm -f *.o rose_*.[cC] rose_*.upc rose_* *.dot
	rm -rf QMTest

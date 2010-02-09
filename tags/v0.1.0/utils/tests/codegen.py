import string

def ProcessSourceFile(basename):
    fp = file(basename + '.cpp','w')
    line1 = basename.upper()
    testclass = basename.replace('TestCase','')
    fp.writelines('#include "' + basename + '.h"\n')
    fp.writelines('\n')
    fp.writelines('CPPUNIT_TEST_SUITE_REGISTRATION( ' + basename + ' );\n')
    fp.writelines('\n')
    fp.writelines('void ' + basename + '::setUp()\n')
    fp.writelines('{\n')
    fp.writelines('}\n')
    fp.writelines('\n')
    fp.writelines('void ' + basename + '::tearDown()\n')
    fp.writelines('{\n')
    fp.writelines('}\n')
    fp.writelines('\n')
    fp.writelines('void ' + basename + '::testCDtor()\n')
    fp.writelines('{\n')
    fp.writelines('\ttry {\n')
    fp.writelines('\t\t' +  testclass + ' tc;\n')
    fp.writelines('\t} catch (...) {\n')
    fp.writelines('\t}\n')
    fp.writelines('}\n')
    fp.writelines('\n')
    fp.close()
    
def ProcessHeaderFile(basename):
    fp = file(basename + '.h','w')
    line1 = basename.upper()
    testclassheader = basename.replace('TestCase','') + '.h'
    fp.writelines('#ifndef _' + line1 + '_H_\n')
    fp.writelines('#define _' + line1 + '_H_\n')
    fp.writelines('#include <string>\n')
    fp.writelines('#include <cppunit/extensions/HelperMacros.h>\n')
    fp.writelines('#include <' + testclassheader + '>\n')
    fp.writelines('\n')
    fp.writelines('class ' + basename + ' : public CPPUNIT_NS::TestFixture\n')
    fp.writelines('{\n')
    fp.writelines('\tCPPUNIT_TEST_SUITE( ' + basename + ' );\n')
    fp.writelines('\tCPPUNIT_TEST( testCDtor );\n')
    fp.writelines('\tCPPUNIT_TEST_SUITE_END();\n')
    fp.writelines('public:\n')
    fp.writelines('\tvoid setUp();\n')
    fp.writelines('\tvoid tearDown();\n')
    fp.writelines('\tvoid testCDtor();\n')
    fp.writelines('};\n')
    fp.writelines('\n')
    fp.writelines('#endif // _' + line1 + '_H_\n')
    fp.close()
    
if __name__ == "__main__":
    filenames = ['ArchiveHandleManagerTestCase',
                 'BasisManagerTestCase',
                 'ContextHandleManagerTestCase',
                 'DeclarationManagerTestCase',
                 'ErrorHandlerManagerTestCase',
                 'FilterFuncManagerTestCase',
                 'LightHandleManagerTestCase',
                 'ObjectHandleManagerTestCase',
                 'TParameterListTestCase']

    for item in filenames:
        ProcessHeaderFile(item)
        ProcessSourceFile(item)
    
    

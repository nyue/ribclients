// -*- C++ -*-
// Procedural Insight 2007 

// Typemaps and other stuff specific to Python support

%typemap(in) (RtPointer o_result,
	      RtInt i_resultlen,
              RxInfoType_t *o_resulttype,
              RtInt *o_resultcount)
{
  $1 = 0; // initialize to zero tokens/params pair, $1 is == n
  if ($input != NULL) {
    g_params.Reinitialize();
    g_params.ProcessParameterList($input);
    $1 = g_params.size();
    // std::cout << "g_params.size() returned " << $1 << std::endl;
    if ($1 > 0) {
      $2 = g_params.GetRIBClientCompatibleTokens();
      $3 = g_params.GetRIBClientCompatibleParms();
    } else {
      $2 = (RtToken *)0;
      $3 = (RtPointer *)0;
    }
  }
}

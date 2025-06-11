auto add_include_dir(TString incdir) {
    std::cout << "Adding to include dirs: " << incdir << "\n";
    incdir.Prepend( ".include ");
    gROOT->ProcessLine( incdir.Data(), NULL );
}

void rootlogon(TString additional_libs           = "",
               TString load_from_second_location = "",
               TString personal_lib_list         = "",
               Bool_t  test_mode                 = kFALSE)
{
    gSystem->Load("libroot_demo");

    gSystem->SetMakeSharedLib(
        "cd $BuildDir; echo \"Building in $(pwd)\";"
        "g++ -std=c++23 -c $Opt -pipe -Wall -fPIC -pthread $IncludePath $SourceFiles; "
        "g++ $ObjectFiles -shared -Wl,-soname,$LibName.so "
        "-O $LinkedLibs -o $SharedLib");
}

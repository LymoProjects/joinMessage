add_rules("mode.debug", "mode.release")

set_languages("c++20")
set_runtimes("MD")

target("join_message") 
    set_kind("shared")

    add_defines(
        "NDEBUG",
        "NOMINMAX",
        "TEMPLATE_EXPORTS",
        "UNICODE",
        "WIN32_LEAN_AND_MEAN",
        "_AMD64_",
        "_CRT_SECURE_NO_WARNINGS",
        "_UNICODE",
        "_USRDLL",
        "_WINDLL",
        "_WINDOWS"
    )

    add_cxflags(
        "/diagnostics:column",
        "/EHsc",
        "/FC",
        "/GL",
        "/MD",
        "/nologo",
        "/permissive-",
        "/sdl",
        "/utf-8",
        "/Zc:inline",
        "/Zi",
        "/FS"
    )

    add_shflags(
        "/DEBUG",
        "/DELAYLOAD:bedrock_server.dll",
        "/DLL",
        "/IGNORE:4199",
        "/INCREMENTAL:NO",
        "/LTCG:INCREMENTAL",
        "/MANIFESTUAC:NO",
        "/MACHINE:X64",
        "/NOLOGO",
        "/OPT:ICF",
        "/OPT:REF",
        "/SUBSYSTEM:CONSOLE"
    )

    add_files(
        "src/*.cpp"
    )

    add_syslinks(
        "Advapi32",
        "Crypt32",
        "Wldap32"
    )

    add_links(
        "LiteLoader",
        "bedrock_server_api",
        "bedrock_server_var",
        "SymDBHelper",
        "co",
        "libcurl",
        "libssl",
        "libcrypto"
    )

    add_includedirs(
        "src",
        "include",
        "SDK/include",
        "D:/Cds/Libs/MD/coost/include"
    )

    add_linkdirs(
        "SDK/lib",
        "D:/Cds/Libs/MD/coost/build/windows/x64/release",
        "D:/Cds/Libs/curl-7.88.1/build/artifacts/l/libcurl/7.87.0/a2ac3a70b1e948b1843919b4cbb41b7f/lib",
        "D:/Cds/Libs/openssl-3.0.8/build/artifacts/o/openssl/1.1.1-t/9458079689e342b58f2f2e8d4b2fb860/lib"
    )
target_end()
{
    "targets": [
        {
            "target_name": "node-hashint",
            "cflags!": [ "-fno-exceptions" ],
            "cflags_cc!": [ "-fno-exceptions" ],
            "sources": [
                "./src/index.cpp",
                "./src/hashint8.cpp",
                "./src/hashint16.cpp"
            ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")"
            ],
            'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
        }
    ]
}
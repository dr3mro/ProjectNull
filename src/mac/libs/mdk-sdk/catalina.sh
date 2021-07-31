THIS_DIR="$(cd "$(dirname ${BASH_SOURCE[0]})";pwd -P)"

xattr -p com.apple.quarantine "$THIS_DIR"/lib/lib*.dylib "$THIS_DIR"/lib/mdk.framework "$THIS_DIR"/bin/*
xattr -dr com.apple.quarantine "$THIS_DIR"/lib/lib*.dylib "$THIS_DIR"/lib/mdk.framework "$THIS_DIR"/bin/*
find "$THIS_DIR" -name mdk.framework -exec xattr -dr com.apple.quarantine {} \;
find "$THIS_DIR" -name "*.dylib" -exec xattr -dr com.apple.quarantine {} \;

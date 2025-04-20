# Enabling and Disabling Unit Tests in CLion with CMake

This project uses a configurable CMake flag called `ENABLE_TESTS` to control whether unit test files are included in the build.

## ✅ Default Behavior
By default, tests are **enabled**:
```cmake
option(ENABLE_TESTS "Enable unit testing support" ON)
```

This means test code such as `runAllTests()`, `run_cdr_tests()`, and `run_xdr_tests()` is compiled into the plugin unless explicitly turned off.

---

## 🔧 Turning Tests Off (in CLion)

To disable test code:

1. **Open CLion Preferences**:
    - `File → Settings` (Windows/Linux)
    - `CLion → Preferences` (macOS)

2. Navigate to:
    - `Build, Execution, Deployment → CMake`

3. In the **CMake options** field for your profile (e.g., Debug), enter:
```bash
-DENABLE_TESTS=OFF
```

4. Click **Apply**, then **OK**.

5. CLion will reconfigure the project. Test code and test-related plugin commands will no longer be compiled.

---

## ✅ Turning Tests Back On
To re-enable tests:
- Go back to the **CMake options** field
- Change to:
```bash
-DENABLE_TESTS=ON
```
- Click **Apply**, then **OK**

---

## 🧪 Test Command
If tests are enabled, the plugin will register a command:
```text
custom/test/run_all_tests
```
You can:
- Trigger this via **DRT** or **DataRefTool**
- Bind it to a key

This command runs all registered test groups:
- `run_cdr_tests()` for custom datarefs
- `run_xdr_tests()` for native datarefs

---

## 📦 Tip
You do **not** need to edit `CMakeLists.txt` every time. Just toggle the flag using CMake options.

If building from the command line:
```bash
cmake -DENABLE_TESTS=OFF .
```


function info = colorflowSetupSdkDllPath(sdk_root)

    if nargin < 1 || isempty(sdk_root)
        sdk_root = fileparts(fileparts(mfilename('fullpath')));
    end

    deps_dir = strtrim(getenv('US_ACQ_COLORFLOW_DEPS'));
    if isempty(deps_dir)
        deps_dir = 'C:\CC\dll';
    end

    data_dir = strtrim(getenv('US_ACQ_COLORFLOW_DATA_DIR'));
    if isempty(data_dir)
        data_dir = 'C:\CC\data';
        setenv('US_ACQ_COLORFLOW_DATA_DIR', data_dir);
    end

    lib_dir = fullfile(sdk_root, 'lib');
    prepend = {};
    if isfolder(deps_dir)
        prepend{end+1} = deps_dir; 
    end
    if isfolder(lib_dir)
        prepend{end+1} = lib_dir; 
    end
    if ~isempty(prepend)
        setenv('PATH', [strjoin(prepend, ';') ';' getenv('PATH')]);
    end

    info.deps_dir = deps_dir;
    info.data_dir = data_dir;
    info.lib_dir = lib_dir;
    info.dll_path = fullfile(lib_dir, 'US_ACQ_ALG_SDK.dll');
    info.header_path = fullfile(lib_dir, 'US_ACQ_ALG_SDK_MATLAB.h');
end

Product()
{
    web_reg_save_param_json(
        "ParamName=ProductResponse",
        "QueryString=$",
        LAST);

    web_add_header("Authorization", "Bearer {authToken}");
    web_add_header("Accept", "application/json");

    web_custom_request("Product_API",
        "URL=https://api.edp.henryschein.com/api/catalogs/{catalogname}/products?itemCode={itemCode}",
        "Method=GET",
        "Resource=0",
        "RecContentType=application/json",
        "Mode=HTTP",
        LAST);

    {
        int statusCode;
        statusCode = web_get_int_property(HTTP_INFO_RETURN_CODE);

        if (statusCode != 200)
        {
            lr_error_message("Response Code: %d", statusCode);
            return -1;
        }

        lr_output_message("Response Code: %d", statusCode);
    }

    lr_output_message("Catalog: %s | ItemCode: %s",
        lr_eval_string("{catalogname}"),
        lr_eval_string("{itemCode}"));

    lr_output_message("Response JSON:\n%s",
        lr_eval_string("{ProductResponse}"));

    return 0;
}

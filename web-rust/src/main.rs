use axum::{Router, routing::get};
use tower_http::services::ServeDir;

async fn flag_handler()
-> Result<axum::response::Response<axum::body::Body>, std::convert::Infallible> {
    let flag = std::env::var("FLAG").unwrap_or_else(|_| "flag{test}".to_string());
    Ok(axum::response::Response::builder()
        .header("Content-Type", "text/html")
        .body(axum::body::Body::from(format!(
            "<strong>Here is your flag: </strong>{}",
            flag
        )))
        .unwrap())
}

async fn handle_robots(flag_path: String) -> String {
    format!("User-agent: *\nDisallow: {}", flag_path)
}

#[tokio::main]
async fn main() {
    let bind_addr = std::env::var("BIND_ADDR").unwrap_or_else(|_| "0.0.0.0:80".to_string());
    let static_path = std::env::var("STATIC_PATH").unwrap_or_else(|_| "/var/www/html".to_string());

    let serve_dir = ServeDir::new(&static_path)
        .append_index_html_on_directories(true)
        .not_found_service(tower::service_fn(|_| async {
            Ok::<_, std::convert::Infallible>(
                axum::response::Response::builder()
                    .status(axum::http::StatusCode::NOT_FOUND)
                    .body(axum::body::Body::from("404 Not Found"))
                    .unwrap(),
            )
        }));

    // flag_path = '/f1ag_' + random hex string
    let randhex = std::iter::repeat_with(rand::random::<u8>)
        .take(8)
        .fold(String::new(), |acc, byte| {
            acc + &format!("{:02x}", byte)
        });
    let flag_path = format!("/f1ag_{}", randhex);

    // Build application with routes and middleware
    let app = Router::new()
        .route(
            "/robots.txt",
            get({
                let flag_path = flag_path.clone();
                move || handle_robots(flag_path)
            }),
        )
        .route(&flag_path, get(flag_handler))
        .fallback_service(serve_dir);

    // Start server
    let listener = tokio::net::TcpListener::bind(bind_addr).await.unwrap();
    let addr = listener.local_addr().unwrap();
    println!("Listening on {}", addr);
    if let Err(e) = axum::serve(listener, app).await {
        eprintln!("Server error: {}", e);
    }
}
